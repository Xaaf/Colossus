#pragma once

#ifdef _WIN32
#ifdef OBELISK_EXPORTS
        #define OBELISK_API __declspec(dllexport)
#else
        #define OBELISK_API __declspec(dllimport)
#endif
#else
#define OBELISK_API
#endif