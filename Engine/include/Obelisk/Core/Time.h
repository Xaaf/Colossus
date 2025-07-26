#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {

/**
 * @brief Time management class for delta time, frame timing, and performance
 * metrics
 *
 * The Time class provides a centralized system for all time-related operations
 * in the engine. It tracks frame delta time, maintains frame rate statistics,
 * and provides utilities for time-based calculations and performance
 * monitoring.
 *
 * Key features:
 * - Frame delta time calculation
 * - Frame rate tracking (FPS, average FPS, min/max FPS)
 * - Total elapsed time since startup
 * - Frame time history for smoothing and analysis
 * - Time scaling support for slow motion or fast forward effects
 * - High-precision timing using std::chrono
 *
 * @example
 * ```cpp
 * // Update time each frame
 * Time::Update();
 *
 * // Use delta time for frame-independent movement
 * float speed = 5.0f; // units per second
 * position += velocity * speed * Time::GetDeltaTime();
 *
 * // Check performance
 * if (Time::GetFPS() < 30.0f) {
 *     LOG_WARN("Low frame rate detected: {:.1f} FPS", Time::GetFPS());
 * }
 * ```
 */
class OBELISK_API Time {
    public:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;
        using Duration = std::chrono::duration<float>;

    private:
        static TimePoint s_StartTime;         ///< Engine start time
        static TimePoint s_LastFrameTime;     ///< Previous frame timestamp
        static TimePoint s_CurrentFrameTime;  ///< Current frame timestamp

        static float s_DeltaTime;  ///< Time since last frame (seconds)
        static float s_TotalTime;  ///< Total time since engine start (seconds)
        static float s_TimeScale;  ///< Time scaling factor (1.0 = normal speed)
        static float
            s_MaxDeltaTime;  ///< Maximum delta time cap to prevent large jumps

        // Frame rate tracking
        static float s_FPS;         ///< Current frames per second
        static float s_AverageFPS;  ///< Rolling average FPS
        static float s_MinFPS;      ///< Minimum FPS recorded this session
        static float s_MaxFPS;      ///< Maximum FPS recorded this session

        // Frame timing history for smoothing
        static constexpr size_t FRAME_HISTORY_SIZE =
            60;  ///< Number of frames to track
        static std::array<float, FRAME_HISTORY_SIZE> s_FrameTimeHistory;
        static size_t s_FrameHistoryIndex;  ///< Current index in frame history
        static size_t s_FrameCount;         ///< Total frames processed
        static bool s_HistoryFilled;  ///< Whether frame history buffer is full

        // Performance tracking
        static float s_FrameTimeSum;       ///< Sum of recent frame times
        static TimePoint s_LastFPSUpdate;  ///< Last time FPS was calculated

    public:
        /**
         * @brief Initialize the time system
         *
         * Should be called once during engine initialization to set up
         * the time system and record the start time.
         */
        static void Initialize();

        /**
         * @brief Update time calculations
         *
         * Should be called once per frame to update delta time, frame rate,
         * and other timing statistics. Typically called at the beginning
         * of the main loop.
         */
        static void Update();

        // === Delta Time ===

        /**
         * @brief Get time elapsed since last frame
         * @return Delta time in seconds (scaled by time scale)
         */
        static float GetDeltaTime();

        /**
         * @brief Get unscaled delta time
         * @return Raw delta time in seconds (unaffected by time scale)
         */
        static float GetUnscaledDeltaTime();

        /**
         * @brief Get total elapsed time since engine start
         * @return Total time in seconds (scaled by time scale)
         */
        static float GetTotalTime();

        /**
         * @brief Get unscaled total time
         * @return Raw total time in seconds (unaffected by time scale)
         */
        static float GetUnscaledTotalTime();

        // === Time Scaling ===

        /**
         * @brief Set time scaling factor
         * @param scale Time scale (1.0 = normal, 0.5 = half speed, 2.0 = double
         * speed, 0.0 = pause)
         */
        static void SetTimeScale(float scale);

        /**
         * @brief Get current time scaling factor
         * @return Time scale value
         */
        static float GetTimeScale();

        /**
         * @brief Set maximum allowed delta time
         * @param maxDelta Maximum delta time in seconds (prevents large jumps)
         */
        static void SetMaxDeltaTime(float maxDelta);

        /**
         * @brief Get maximum delta time cap
         * @return Maximum delta time in seconds
         */
        static float GetMaxDeltaTime();

        // === Frame Rate Tracking ===

        /**
         * @brief Get current frames per second
         * @return Current FPS
         */
        static float GetFPS();

        /**
         * @brief Get rolling average FPS
         * @return Average FPS over recent frames
         */
        static float GetAverageFPS();

        /**
         * @brief Get minimum FPS recorded this session
         * @return Minimum FPS
         */
        static float GetMinFPS();

        /**
         * @brief Get maximum FPS recorded this session
         * @return Maximum FPS
         */
        static float GetMaxFPS();

        /**
         * @brief Get total number of frames processed
         * @return Frame count
         */
        static size_t GetFrameCount();

        /**
         * @brief Reset FPS statistics
         *
         * Clears min/max FPS tracking and resets averages.
         * Useful when transitioning between scenes or after loading.
         */
        static void ResetFPSStats();

        // === Frame Time Analysis ===

        /**
         * @brief Get frame time in milliseconds
         * @return Current frame time in milliseconds
         */
        static float GetFrameTimeMS();

        /**
         * @brief Get average frame time in milliseconds
         * @return Average frame time in milliseconds
         */
        static float GetAverageFrameTimeMS();

        /**
         * @brief Check if frame rate is stable
         * @param threshold FPS variation threshold (default: 5.0)
         * @return True if FPS is relatively stable
         */
        static bool IsFrameRateStable(float threshold = 5.0f);

        // === Utility Methods ===

        /**
         * @brief Check if enough time has passed since last check
         * @param interval Interval in seconds
         * @param lastTime Reference to time variable to update
         * @return True if interval has elapsed
         */
        static bool HasIntervalPassed(float interval, float& lastTime);

        /**
         * @brief Get current system time as string
         * @return Formatted time string (HH:MM:SS)
         */
        static std::string GetCurrentTimeString();

        /**
         * @brief Convert seconds to formatted string
         * @param seconds Time in seconds
         * @return Formatted time string (MM:SS or HH:MM:SS)
         */
        static std::string FormatTime(float seconds);

    private:
        /**
         * @brief Update frame rate calculations
         */
        static void UpdateFrameRate();

        /**
         * @brief Update frame time history
         */
        static void UpdateFrameHistory();
};

}  // namespace Obelisk
