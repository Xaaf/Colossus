#include "Obelisk/Core/Time.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <sstream>
#include "Obelisk/Logging/Log.h"


namespace Obelisk {

// Static member definitions
Time::TimePoint Time::s_StartTime;
Time::TimePoint Time::s_LastFrameTime;
Time::TimePoint Time::s_CurrentFrameTime;

float Time::s_DeltaTime = 0.0f;
float Time::s_TotalTime = 0.0f;
float Time::s_TimeScale = 1.0f;
float Time::s_MaxDeltaTime = 1.0f / 20.0f;  // Cap at 20 FPS (0.05 seconds)

float Time::s_FPS = 0.0f;
float Time::s_AverageFPS = 0.0f;
float Time::s_MinFPS = std::numeric_limits<float>::max();
float Time::s_MaxFPS = 0.0f;

std::array<float, Time::FRAME_HISTORY_SIZE> Time::s_FrameTimeHistory{};
size_t Time::s_FrameHistoryIndex = 0;
size_t Time::s_FrameCount = 0;
bool Time::s_HistoryFilled = false;

float Time::s_FrameTimeSum = 0.0f;
Time::TimePoint Time::s_LastFPSUpdate;

void Time::Initialize() {
    s_StartTime = Clock::now();
    s_LastFrameTime = s_StartTime;
    s_CurrentFrameTime = s_StartTime;
    s_LastFPSUpdate = s_StartTime;

    // Initialize frame history
    s_FrameTimeHistory.fill(1.0f / 60.0f);  // Assume 60 FPS initially
    s_FrameHistoryIndex = 0;
    s_FrameCount = 0;
    s_HistoryFilled = false;
    s_FrameTimeSum = (1.0f / 60.0f) * FRAME_HISTORY_SIZE;

    // Reset statistics
    s_DeltaTime = 0.0f;
    s_TotalTime = 0.0f;
    s_FPS = 60.0f;
    s_AverageFPS = 60.0f;
    s_MinFPS = std::numeric_limits<float>::max();
    s_MaxFPS = 0.0f;

    LOG_INFO("Time system initialized");
}

void Time::Update() {
    s_CurrentFrameTime = Clock::now();

    // Calculate delta time
    Duration deltaTimeDuration = s_CurrentFrameTime - s_LastFrameTime;
    s_DeltaTime = deltaTimeDuration.count();

    // Cap delta time to prevent large jumps (e.g., during debugging or loading)
    s_DeltaTime = std::min(s_DeltaTime, s_MaxDeltaTime);

    // Update total time
    s_TotalTime += s_DeltaTime;

    // Update frame tracking
    s_FrameCount++;
    UpdateFrameHistory();
    UpdateFrameRate();

    // Update for next frame
    s_LastFrameTime = s_CurrentFrameTime;
}

float Time::GetUnscaledTotalTime() {
    Duration totalDuration = s_CurrentFrameTime - s_StartTime;
    return totalDuration.count();
}

// === Getter implementations ===

float Time::GetDeltaTime() { return s_DeltaTime * s_TimeScale; }

float Time::GetUnscaledDeltaTime() { return s_DeltaTime; }

float Time::GetTotalTime() { return s_TotalTime; }

void Time::SetTimeScale(float scale) { s_TimeScale = std::max(0.0f, scale); }

float Time::GetTimeScale() { return s_TimeScale; }

void Time::SetMaxDeltaTime(float maxDelta) { s_MaxDeltaTime = maxDelta; }

float Time::GetMaxDeltaTime() { return s_MaxDeltaTime; }

float Time::GetFPS() { return s_FPS; }

float Time::GetAverageFPS() { return s_AverageFPS; }

float Time::GetMinFPS() { return s_MinFPS; }

float Time::GetMaxFPS() { return s_MaxFPS; }

size_t Time::GetFrameCount() { return s_FrameCount; }

float Time::GetFrameTimeMS() { return s_DeltaTime * 1000.0f; }

void Time::ResetFPSStats() {
    s_MinFPS = std::numeric_limits<float>::max();
    s_MaxFPS = 0.0f;
    s_AverageFPS = s_FPS;

    LOG_INFO("FPS statistics reset");
}

float Time::GetAverageFrameTimeMS() {
    if (!s_HistoryFilled && s_FrameHistoryIndex == 0) {
        return s_DeltaTime * 1000.0f;
    }

    size_t count = s_HistoryFilled ? FRAME_HISTORY_SIZE : s_FrameHistoryIndex;
    float averageFrameTime = s_FrameTimeSum / static_cast<float>(count);
    return averageFrameTime * 1000.0f;
}

bool Time::IsFrameRateStable(float threshold) {
    if (!s_HistoryFilled && s_FrameHistoryIndex < 10) {
        return true;  // Not enough data yet
    }

    size_t count = s_HistoryFilled ? FRAME_HISTORY_SIZE : s_FrameHistoryIndex;

    // Calculate variance in frame times
    float mean = s_FrameTimeSum / static_cast<float>(count);
    float variance = 0.0f;

    for (size_t i = 0; i < count; ++i) {
        float diff = s_FrameTimeHistory[i] - mean;
        variance += diff * diff;
    }
    variance /= static_cast<float>(count);

    float standardDeviation = std::sqrt(variance);
    float coefficientOfVariation = (standardDeviation / mean) * 100.0f;

    return coefficientOfVariation <= threshold;
}

bool Time::HasIntervalPassed(float interval, float& lastTime) {
    if (s_TotalTime - lastTime >= interval) {
        lastTime = s_TotalTime;
        return true;
    }
    return false;
}

std::string Time::GetCurrentTimeString() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &time_t);
#else
    tm = *std::localtime(&time_t);
#endif

    std::stringstream ss;
    ss << std::put_time(&tm, "%H:%M:%S");
    return ss.str();
}

std::string Time::FormatTime(float seconds) {
    int totalSeconds = static_cast<int>(seconds);
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int secs = totalSeconds % 60;

    std::stringstream ss;
    if (hours > 0) {
        ss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2)
           << minutes << ":" << std::setw(2) << secs;
    } else {
        ss << std::setfill('0') << std::setw(2) << minutes << ":"
           << std::setw(2) << secs;
    }

    return ss.str();
}

void Time::UpdateFrameRate() {
    // Calculate instantaneous FPS
    if (s_DeltaTime > 0.0f) {
        s_FPS = 1.0f / s_DeltaTime;
    }

    // Update min/max FPS (ignore very first few frames)
    if (s_FrameCount > 5) {
        s_MinFPS = std::min(s_MinFPS, s_FPS);
        s_MaxFPS = std::max(s_MaxFPS, s_FPS);
    }

    // Update average FPS using frame history
    if (s_FrameTimeSum > 0.0f) {
        size_t count =
            s_HistoryFilled ? FRAME_HISTORY_SIZE : s_FrameHistoryIndex;
        float averageFrameTime = s_FrameTimeSum / static_cast<float>(count);
        s_AverageFPS = 1.0f / averageFrameTime;
    }
}

void Time::UpdateFrameHistory() {
    // Remove old frame time from sum
    s_FrameTimeSum -= s_FrameTimeHistory[s_FrameHistoryIndex];

    // Add new frame time
    s_FrameTimeHistory[s_FrameHistoryIndex] = s_DeltaTime;
    s_FrameTimeSum += s_DeltaTime;

    // Update index
    s_FrameHistoryIndex = (s_FrameHistoryIndex + 1) % FRAME_HISTORY_SIZE;

    // Check if we've filled the buffer for the first time
    if (!s_HistoryFilled && s_FrameHistoryIndex == 0) {
        s_HistoryFilled = true;
    }
}

}  // namespace Obelisk
