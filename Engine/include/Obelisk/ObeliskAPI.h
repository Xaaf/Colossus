#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Core/AssetManager.h"
#include "Obelisk/Renderer/Window.h"

namespace Obelisk {

/**
 * @brief Main engine API class providing the primary interface for engine
 * lifecycle management.
 *
 * The ObeliskAPI class serves as the central entry point for the Colossus game
 * engine. It manages engine initialization, the main game loop, and cleanup
 * using a singleton pattern. Applications interact with the engine through this
 * interface to set up callbacks, configure the window, and control engine
 * execution.
 *
 * @example
 * ```cpp
 * // Basic engine usage
 * auto& engine = Obelisk::ObeliskAPI::Get();
 * engine.SetInitCallback([]() {
 *     // Initialize game objects
 * });
 * engine.SetUpdateCallback([]() {
 *     // Update game logic
 * });
 * engine.Init(1280, 720, "My Game");
 * engine.Run();
 * engine.Shutdown();
 * ```
 */
class OBELISK_API ObeliskAPI {
    private:
        std::function<void()>
            m_InitCallback;  ///< User-defined initialization callback
        std::function<void()>
            m_UpdateCallback;  ///< User-defined update callback (called each
                               ///< frame)
        std::function<void()>
            m_ShutdownCallback;  ///< User-defined shutdown cleanup callback

        std::unique_ptr<Window>
            m_Window;  ///< Main application window (managed via RAII)

    public:
        /**
         * @brief Get the singleton instance of the engine API.
         *
         * Uses Meyer's singleton pattern for thread-safe initialization
         * and automatic cleanup on program termination.
         *
         * @return Reference to the singleton ObeliskAPI instance
         */
        static ObeliskAPI& Get();

        /**
         * @brief Set the initialization callback function.
         *
         * This callback is executed once during engine initialization,
         * after the window is created but before the main loop starts.
         * Use this to initialize game objects, load assets, and set up scenes.
         *
         * @param callback Function to call during engine initialization
         */
        void SetInitCallback(std::function<void()> callback);

        /**
         * @brief Set the update callback function.
         *
         * This callback is executed every frame during the main loop.
         * Use this to update game logic, physics, AI, and other per-frame
         * operations.
         *
         * @param callback Function to call each frame
         */
        void SetUpdateCallback(std::function<void()> callback);

        /**
         * @brief Set the shutdown callback function.
         *
         * This callback is executed during engine shutdown, before window
         * destruction. Use this to save game state, clean up resources, and
         * perform final cleanup.
         *
         * @param callback Function to call during engine shutdown
         */
        void SetShutdownCallback(std::function<void()> callback);

        /**
         * @brief Initialize the engine with specified window parameters.
         *
         * Creates the main window, initializes graphics systems, sets up the
         * AssetManager, and calls the user-defined initialization callback if
         * set.
         *
         * @param width Window width in pixels (default: 640)
         * @param height Window height in pixels (default: 480)
         * @param title Window title text (default: "Obelisk")
         */
        void Init(int width = 640, int height = 480,
                  const char* title = "Obelisk");

        /**
         * @brief Start the main engine loop.
         *
         * Begins the main game loop, which continues until the window is
         * closed. Each iteration calls the update callback (if set) and renders
         * the current frame. This function blocks until the application should
         * terminate.
         */
        void Run();

        /**
         * @brief Shutdown the engine and clean up resources.
         *
         * Calls the shutdown callback (if set), destroys the window,
         * terminates graphics systems, and performs final cleanup.
         */
        void Shutdown();

        /**
         * @brief Get a pointer to the main window.
         *
         * Provides access to the window object for setting scenes,
         * querying window properties, and other window-related operations.
         *
         * @return Pointer to the main Window object, or nullptr if not
         * initialized
         */
        Window* GetWindow() { return m_Window.get(); };

    private:
        /**
         * @brief Private constructor for singleton pattern.
         */
        ObeliskAPI() = default;

        /**
         * @brief Private destructor for singleton pattern.
         */
        ~ObeliskAPI() = default;

        // Delete copy constructor and assignment operator to maintain singleton
        ObeliskAPI(const ObeliskAPI&) = delete;
        ObeliskAPI& operator=(const ObeliskAPI&) = delete;
};
}  // namespace Obelisk