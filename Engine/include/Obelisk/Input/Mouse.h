#ifndef MOUSE_H
#define MOUSE_H

#include "ObeliskPCH.h"
#include <array>
#include <glm/vec2.hpp>
#include <unordered_set>
#include "Obelisk/Input/InputCodes.h"

namespace Obelisk {
/**
 * @brief Manages mouse input for the engine.
 *
 * Provides static methods to handle mouse events. It allows registering
 * per-button actions, as well as keeping account of the mouse's X and Y
 * positions. Also, it allows for querying the different mouse buttons and
 * position through their respective methods.
 */
class Mouse {
    private:
        /**
         * @brief Mouse button states array
         */
        static std::array<bool, OB_MOUSE_BUTTON_LAST + 1> s_Buttons;

        /**
         * @brief Buttons that were previously pressed
         */
        static std::vector<int> s_PreviousButtons;

        /**
         * @brief Current mouse position
         */
        static glm::vec2 s_Position;

    public:
        /**
         * @brief Registers a mouse action.
         *
         * This function registers an action related to mouse input, e.g.
         * pressing or releasing a specific mouse button.
         *
         * @param button The keycode representing the mouse button which fired
         * the event.
         * @param action The action that triggered the event.
         */
        static void RegisterAction(int button, int action);

        /**
         * @brief Registers a mouse movement.
         *
         * This function registers a mouse movement, updating the current X and
         * Y positions of the mouse. These being tracked in the Mouse instance
         * through this function.
         *
         * @param newX The new X position of the mouse, relative to the game
         * window.
         * @param newY The new Y position of the mouse, relative to the game
         * window.
         */
        static void RegisterMove(double newX, double newY);

        /**
         * @brief Checks if a mouse button is currently being pressed down.
         *
         * @param button The keycode representing the mouse button to check.
         * @return True if the mouse button is being held down, false otherwise.
         */
        static bool IsButtonDown(int button);

        /**
         * @brief Checks if a mouse button has been pressed this frame.
         *
         * @param button The keycode representing the mouse button to check.
         * @return True if the mouse button was just pressed this frame, false
         * otherwise.
         */
        static bool IsButtonPressed(int button);

        /**
         * @brief Get the current mouse position.
         *
         * This function returns the current position of the mouse, which is
         * being tracked in the Mouse instance.
         *
         * @return The mouse's X and Y posititions in a Vector2.
         */
        static glm::vec2 GetMousePosition();

        /**
         * @brief Clears the just-pressed state for end of frame processing.
         * This should be called at the end of each frame.
         */
        static void EndFrame();
};
}  // namespace Obelisk

#endif  // MOUSE_H