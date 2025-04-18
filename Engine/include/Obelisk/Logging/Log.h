#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Colours.h"
#include "LogLevels.h"

#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG

/**
 * @brief Fetches the current time in the `HH:MM:SS` format.
 *
 * @return Current time in the format.
 */
inline std::string currentTimeFormatted() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) %
                  1000;

    std::tm local_tm = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%H:%M:%S") << "." << std::setfill('0')
        << std::setw(3) << millis.count();
    return oss.str();
}

/**
 * @brief Formats the given filename to just the filename.
 *
 * Strips off the absolute path, yielding just the filename, without extension.
 *
 * @param filename Filename (with its path) to strip.
 * @param tag Tag to use in the filename.
 * @return Formatted filename, in the form of "Filename#Tag".
 */
inline std::string currentFileFormatted(const std::string& filename,
                                        const std::string& tag) {
    size_t last_slash = filename.find_last_of("/\\");
    std::string file = (last_slash == std::string::npos)
                           ? filename
                           : filename.substr(last_slash + 1);

    size_t last_dot = file.find_last_of(".");
    if (last_dot != std::string::npos) {
        file = file.substr(0, last_dot);
    }

    if (tag.empty()) {
        return file;
    }

    return file + "#" + tag;
}

#define LOG(level, color, levelStr, tag, message)                        \
    do {                                                                 \
        if (level >= CURRENT_LOG_LEVEL) {                                \
            std::cerr << WHITE << currentTimeFormatted() << " " << color \
                      << "[" << levelStr << ": "                         \
                      << currentFileFormatted(__FILE__, tag) << "] "     \
                      << message << RESET << std::endl;                  \
        }                                                                \
    } while (0)

#define GET_MACRO(_1, _2, NAME, ...) NAME

#define LOG_TRACE(...) \
    GET_MACRO(__VA_ARGS__, LOG_TRACE_WITH_TAG, LOG_TRACE_NO_TAG)(__VA_ARGS__)
#define LOG_TRACE_WITH_TAG(tag, message) \
    LOG(LOG_LEVEL_TRACE, CYAN, "TRC", tag, message)
#define LOG_TRACE_NO_TAG(message) LOG(LOG_LEVEL_TRACE, CYAN, "TRC", "", message)

#define LOG_DEBUG(...) \
    GET_MACRO(__VA_ARGS__, LOG_DEBUG_WITH_TAG, LOG_DEBUG_NO_TAG)(__VA_ARGS__)
#define LOG_DEBUG_WITH_TAG(tag, message) \
    LOG(LOG_LEVEL_DEBUG, MAGENTA, "DBG", tag, message)
#define LOG_DEBUG_NO_TAG(message) \
    LOG(LOG_LEVEL_DEBUG, MAGENTA, "DBG", "", message)

#define LOG_INFO(...) \
    GET_MACRO(__VA_ARGS__, LOG_INFO_WITH_TAG, LOG_INFO_NO_TAG)(__VA_ARGS__)
#define LOG_INFO_WITH_TAG(tag, message) \
    LOG(LOG_LEVEL_INFO, WHITE, "INF", tag, message)
#define LOG_INFO_NO_TAG(message) LOG(LOG_LEVEL_INFO, WHITE, "INF", "", message)

#define LOG_WARN(...) \
    GET_MACRO(__VA_ARGS__, LOG_WARN_WITH_TAG, LOG_WARN_NO_TAG)(__VA_ARGS__)
#define LOG_WARN_WITH_TAG(tag, message) \
    LOG(LOG_LEVEL_WARN, YELLOW, "WRN", tag, message)
#define LOG_WARN_NO_TAG(message) LOG(LOG_LEVEL_WARN, YELLOW, "WRN", "", message)

#define LOG_ERROR(...) \
    GET_MACRO(__VA_ARGS__, LOG_ERROR_WITH_TAG, LOG_ERROR_NO_TAG)(__VA_ARGS__)
#define LOG_ERROR_WITH_TAG(tag, message) \
    LOG(LOG_LEVEL_ERROR, RED, "ERR", tag, message)
#define LOG_ERROR_NO_TAG(message) LOG(LOG_LEVEL_ERROR, RED, "ERR", "", message)
