#pragma once

#include "ObeliskPCH.h"
#include <filesystem>

namespace Obelisk {

/**
 * @brief Manages asset loading and path resolution for the engine.
 *
 * The AssetManager provides a centralized way to handle asset paths,
 * ensuring that assets can be loaded regardless of the working directory
 * and supporting different deployment scenarios.
 */
class OBELISK_API AssetManager {
    private:
        static std::filesystem::path s_AssetBasePath;
        static bool s_Initialized;

        /**
         * @brief Initialize the asset manager with automatic path detection
         */
        static void AutoInitialize();

    public:
        /**
         * @brief Initialize the asset manager with a specific base path
         *
         * @param basePath The base directory containing assets
         */
        static void Initialize(const std::filesystem::path& basePath);

        /**
         * @brief Get the full path to an asset
         *
         * @param relativePath The relative path to the asset (e.g.,
         * "textures/player.png")
         * @return The full filesystem path to the asset
         */
        static std::filesystem::path GetAssetPath(
            const std::string& relativePath);

        /**
         * @brief Check if an asset exists
         *
         * @param relativePath The relative path to the asset
         * @return True if the asset exists, false otherwise
         */
        static bool AssetExists(const std::string& relativePath);

        /**
         * @brief Get the base asset directory
         *
         * @return The base asset directory path
         */
        static const std::filesystem::path& GetBasePath();

        /**
         * @brief Set the base asset directory
         *
         * @param basePath The new base directory for assets
         */
        static void SetBasePath(const std::filesystem::path& basePath);

        /**
         * @brief Get information about asset loading for debugging
         *
         * @return String containing asset manager status and paths
         */
        static std::string GetDebugInfo();

    private:
        /**
         * @brief Find the assets directory relative to the executable
         *
         * @return Path to assets directory, or empty path if not found
         */
        static std::filesystem::path FindAssetsDirectory();

        /**
         * @brief Get the directory containing the current executable
         *
         * @return Path to executable directory
         */
        static std::filesystem::path GetExecutableDirectory();
};

}  // namespace Obelisk
