#pragma once

/**
 * @file Macros.h
 * @brief Platform-specific macro definitions for the Obelisk engine.
 *
 * This header defines macros that handle platform-specific functionality,
 * particularly for Windows DLL export/import declarations. These macros
 * ensure that the engine can be built as both static and dynamic libraries
 * across different platforms.
 */

/**
 * @def OBELISK_API
 * @brief Platform-specific API decoration for exported symbols.
 *
 * This macro handles the platform-specific details of exporting symbols
 * from the engine library:
 *
 * - On Windows when building the engine (OBELISK_EXPORTS defined):
 *   Expands to __declspec(dllexport) to export symbols from the DLL
 *
 * - On Windows when using the engine (OBELISK_EXPORTS not defined):
 *   Expands to __declspec(dllimport) to import symbols from the DLL
 *
 * - On other platforms (Linux, macOS):
 *   Expands to nothing, as these platforms handle symbol visibility differently
 *
 * Usage: Prefix all public engine classes and functions with this macro
 * to ensure proper symbol visibility across platforms.
 *
 * @example
 * ```cpp
 * class OBELISK_API MyEngineClass {
 *     // Class definition
 * };
 *
 * OBELISK_API void MyEngineFunction();
 * ```
 */
#ifdef _WIN32
    #ifdef OBELISK_EXPORTS
        #define OBELISK_API __declspec(dllexport)
    #else
        #define OBELISK_API __declspec(dllimport)
    #endif
#else
    #define OBELISK_API
#endif