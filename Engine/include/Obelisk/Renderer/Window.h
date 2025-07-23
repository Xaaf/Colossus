#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Scene/Scene.h"

namespace Obelisk {

/**
 * @brief Main application window class managing GLFW window and rendering
 * context.
 *
 * The Window class encapsulates GLFW window creation, OpenGL context
 * management, and the main rendering loop. It serves as the primary interface
 * between the engine and the windowing system, handling window events, scene
 * rendering, and frame timing.
 *
 * Key responsibilities:
 * - GLFW window lifecycle management
 * - OpenGL context creation and management
 * - Scene rendering coordination
 * - Input event handling setup
 * - Frame timing and presentation
 *
 * @example
 * ```cpp
 * auto window = std::make_unique<Window>();
 * window->Create(1280, 720, "My Game");
 * window->SetScene(myScene);
 *
 * while (!window->ShouldClose()) {
 *     window->Tick();
 * }
 * ```
 */
class OBELISK_API Window {
    private:
        GLFWwindow* m_Window =
            nullptr;  ///< GLFW window handle (managed by GLFW)
        Scene* m_Scene =
            nullptr;  ///< Currently active scene to render (not owned)

    public:
        /**
         * @brief Default constructor.
         *
         * Creates an uninitialized window object. Call Create() to initialize
         * the actual window and rendering context.
         */
        Window() = default;

        /**
         * @brief Destructor that cleans up GLFW resources.
         *
         * Automatically destroys the GLFW window if it was created
         * successfully. The destructor ensures proper cleanup even if the
         * window object goes out of scope unexpectedly.
         */
        ~Window();

        /**
         * @brief Create and initialize the GLFW window with OpenGL context.
         *
         * Initializes GLFW (if not already done), creates a window with the
         * specified dimensions and title, sets up the OpenGL context, and
         * configures input callbacks for keyboard and mouse handling.
         *
         * @param width Window width in pixels
         * @param height Window height in pixels
         * @param title Window title displayed in the title bar
         * @return 0 on success, non-zero error code on failure
         *
         * @note This method must be called before using any other window
         * functions
         * @note Automatically sets up input callbacks for the engine's input
         * system
         */
        int Create(int width, int height, const std::string& title);

        /**
         * @brief Process one frame of the render loop.
         *
         * Performs a complete frame cycle including:
         * - Processing window and input events via glfwPollEvents()
         * - Clearing the framebuffer
         * - Rendering the current scene (if set)
         * - Swapping front and back buffers for display
         *
         * This method should be called once per frame in the main game loop.
         *
         * @note Does nothing if no scene is set
         * @note Automatically handles OpenGL state management
         */
        void Tick();

        /**
         * @brief Set the scene to be rendered by this window.
         *
         * Associates a scene object with this window for rendering. The scene
         * contains all the entities, components, and rendering state needed
         * to draw the current game state.
         *
         * @param scene Pointer to the scene to render (window does not take
         * ownership)
         *
         * @note Passing nullptr will disable scene rendering
         * @note The caller retains ownership of the scene object
         */
        void SetScene(Scene* scene) { m_Scene = scene; };

        /**
         * @brief Check if the window should be closed.
         *
         * Returns the current state of the window's close flag, which is set
         * when the user clicks the close button, presses Alt+F4, or when
         * glfwSetWindowShouldClose() is called programmatically.
         *
         * @return true if the window should be closed, false otherwise
         *
         * @note This is typically used as the condition for the main game loop
         */
        [[nodiscard]] bool ShouldClose() const;
};

}  // namespace Obelisk