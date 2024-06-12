#ifndef LOG_H
#define LOG_H

#include <iostream>
#include "Colors.h"
#include "LogLevels.h"

#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG

#define LOG(level, color, levelStr, tag, message)                        \
    do {                                                                 \
        if (level >= CURRENT_LOG_LEVEL) {                                \
            std::cerr << color << "[" << levelStr << ": " << tag << "] " \
                      << message << RESET << std::endl;                  \
        }                                                                \
    } while (0)

#define LOG_TRACE(tag, message) \
    LOG(LOG_LEVEL_TRACE, CYAN, "TRACE", tag, message)
#define LOG_DEBUG(tag, message) \
    LOG(LOG_LEVEL_DEBUG, MAGENTA, "DEBUG", tag, message)
#define LOG_INFO(tag, message) LOG(LOG_LEVEL_INFO, WHITE, "INFO", tag, message)
#define LOG_WARN(tag, message) LOG(LOG_LEVEL_WARN, YELLOW, "WARN", tag, message)
#define LOG_ERROR(tag, message) LOG(LOG_LEVEL_ERROR, RED, "ERROR", tag, message)

#endif  // LOG_H
