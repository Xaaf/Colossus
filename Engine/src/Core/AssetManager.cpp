#include "Obelisk/Core/AssetManager.h"
#include <fstream>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <unistd.h>
    #include <climits>
#endif

namespace Obelisk {

std::filesystem::path AssetManager::s_AssetBasePath;
bool AssetManager::s_Initialized = false;

void AssetManager::Initialize(const std::filesystem::path& basePath) {
    s_AssetBasePath = std::filesystem::absolute(basePath);
    s_Initialized = true;

    LOG_INFO("AssetManager initialized with base path: {}", s_AssetBasePath.string());

    if (!std::filesystem::exists(s_AssetBasePath)) {
        LOG_WARN("Asset base path does not exist: {}", s_AssetBasePath.string());
    }
}

void AssetManager::AutoInitialize() {
    if (s_Initialized) return;

    // Try to find assets directory automatically
    std::filesystem::path assetsPath = FindAssetsDirectory();

    if (!assetsPath.empty()) {
        Initialize(assetsPath);
    } else {
        // Fallback to current directory + assets
        Initialize("assets");
        LOG_WARN("Could not auto-detect assets directory, using fallback: assets/");
    }
}

std::filesystem::path AssetManager::GetAssetPath(
    const std::string& relativePath) {
    if (!s_Initialized) {
        AutoInitialize();
    }

    std::filesystem::path fullPath = s_AssetBasePath / relativePath;

    // Normalize the path (resolve .. and . components)
    fullPath = std::filesystem::weakly_canonical(fullPath);

    return fullPath;
}

bool AssetManager::AssetExists(const std::string& relativePath) {
    std::filesystem::path fullPath = GetAssetPath(relativePath);
    bool exists = std::filesystem::exists(fullPath);

    if (!exists) {
        LOG_TRACE("Asset not found: {} (checked: {})", relativePath, fullPath.string());
    }

    return exists;
}

const std::filesystem::path& AssetManager::GetBasePath() {
    if (!s_Initialized) {
        AutoInitialize();
    }
    return s_AssetBasePath;
}

void AssetManager::SetBasePath(const std::filesystem::path& basePath) {
    Initialize(basePath);
}

std::string AssetManager::GetDebugInfo() {
    std::stringstream info;
    info << "\nAssetManager Debug Info:\n";
    info << "  Initialized: " << (s_Initialized ? "Yes" : "No") << "\n";
    info << "  Base Path: "
         << (s_Initialized ? s_AssetBasePath.string() : "Not set") << "\n";
    info << "  Base Path Exists: "
         << (s_Initialized && std::filesystem::exists(s_AssetBasePath) ? "Yes"
                                                                       : "No")
         << "\n";
    info << "  Executable Directory: " << GetExecutableDirectory().string()
         << "\n";
    info << "  Current Working Directory: "
         << std::filesystem::current_path().string();
    return info.str();
}

std::filesystem::path AssetManager::FindAssetsDirectory() {
    std::filesystem::path execDir = GetExecutableDirectory();

    // List of possible asset directory locations relative to executable
    std::vector<std::filesystem::path> candidatePaths = {
        execDir / "assets",                // Same directory as executable
        execDir.parent_path() / "assets",  // Parent directory
        execDir / ".." / "assets",         // Up one level
        execDir / ".." / ".." /
            "assets",  // Up two levels (for build directories)
        std::filesystem::current_path() / "assets"  // Current working directory
    };

    // Check each candidate path
    for (const auto& candidate : candidatePaths) {
        std::filesystem::path normalized =
            std::filesystem::weakly_canonical(candidate);

        if (std::filesystem::exists(normalized) &&
            std::filesystem::is_directory(normalized)) {
            // Verify it's actually an assets directory by checking for common
            // asset files
            bool hasShaders = std::filesystem::exists(normalized / "shaders");
            bool hasTextures = std::filesystem::exists(normalized / "textures");

            if (hasShaders || hasTextures) {
                LOG_INFO("Auto-detected assets directory: {}", normalized.string());
                return normalized;
            }
        }
    }

    LOG_WARN("Could not auto-detect assets directory. Searched locations:");
    for (const auto& candidate : candidatePaths) {
        LOG_WARN("  - {}", std::filesystem::weakly_canonical(candidate).string());
    }

    return {};
}

std::filesystem::path AssetManager::GetExecutableDirectory() {
#ifdef _WIN32
    char path[MAX_PATH];
    DWORD length = GetModuleFileNameA(NULL, path, MAX_PATH);
    if (length > 0) {
        std::filesystem::path execPath(path);
        return execPath.parent_path();
    }
#elif defined(__linux__)
    char path[PATH_MAX];
    ssize_t length = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (length > 0) {
        path[length] = '\0';
        std::filesystem::path execPath(path);
        return execPath.parent_path();
    }
#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::filesystem::path execPath(path);
        return execPath.parent_path();
    }
#endif

    // Fallback to current working directory
    LOG_WARN("Could not determine executable directory, using current working directory");
    return std::filesystem::current_path();
}

}  // namespace Obelisk
