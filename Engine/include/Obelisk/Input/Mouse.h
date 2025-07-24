#ifndef MOUSE_H
#define MOUSE_H

#include "ObeliskPCH.h"
#include <array>
#include <glm/vec2.hpp>
#include "Obelisk/Input/InputCodes.h"

namespace Obelisk {
/**
 * @brief Manages mouse input for the engine.
 *
 * Provides a singleton interface to handle mouse events. It allows registering
 * per-button actions, as well as keeping account of the mouse's X and Y
 * positions. Also, it allows for querying the different mouse buttons and
 * position through their respective methods.
 */
class Mouse {
    private:
        /**
         * @brief Mouse button states array
         */
        std::array<bool, CS_MOUSE_BUTTON_LAST + 1> m_Buttons{};

        /**
         * @brief Pressed buttons for single-press detection
         */
        std::vector<int> m_PressedButtons;

        /**
         * @brief Current mouse position
         */
        glm::vec2 m_Position{0.0f, 0.0f};

    private:
        /**
         * @brief Construct a new Mouse.
         *
         * This constructor is private in order to facilitate the singleton
         * design pattern the class follows.
         */
        Mouse() = default;

        /**
         * @brief Destroy the Mouse object.
         */
        ~Mouse() = default;

        /**
         * @brief Delete copy constructor and assignment operator
         */
        Mouse(const Mouse&) = delete;
        Mouse& operator=(const Mouse&) = delete;

    public:
        /**
         * @brief Get the singleton instance of the Mouse class.
         *
         * This function provides access to the singleton instance of the
         * Mouse class using Meyer's singleton pattern.
         *
         * @return Reference to the singleton instance of the Mouse class.
         */
        static Mouse& getInstance();

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
        void registerAction(int button, int action);

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
        void registerMove(double newX, double newY);

        /**
         * @brief Checks if a mouse button is currently being pressed down.
         *
         * @param button The keycode representing the mouse button to check.
         * @return True if the mouse button is being held down, false otherwise.
         */
        bool isButtonDown(int button) const;

        /**
         * @brief Checks if a mouse button has been pressed.
         *
         * @param button The keycode representing the mouse button to check.
         * @return True if the mouse button has been pressed, false otherwise.
         */
        bool isButtonPressed(int button);

        /**
         * @brief Get the current mouse position.
         *
         * This function returns the current position of the mouse, which is
         * being tracked in the Mouse instance.
         *
         * @return The mouse's X and Y posititions in a Vector2.
         */
        glm::vec2 getMousePosition() const;
};
}  // namespace Obelisk

#endif  // MOUSE_H