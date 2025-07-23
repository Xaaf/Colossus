#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ObeliskPCH.h"
#include <array>
#include "Obelisk/Input/InputCodes.h"


namespace Obelisk {
/**
 * @brief Manages keyboard input for the engine.
 *
 * Provides a singleton interface to handle keyboard events. It allows
 * registering per-key actions and the querying of said keys through their
 * respective methods.
 */
class Keyboard {
    private:
        /**
         * @brief Key states array
         */
        std::array<bool, CS_KEY_LAST + 1> m_Keys{};

        /**
         * @brief Pressed keys for single-press detection
         */
        std::vector<int> m_PressedKeys;

    private:
        /**
         * @brief Construct a new Keyboard
         *
         * This constructor is private in order to facilitate the singleton
         * design pattern the class follows.
         */
        Keyboard() = default;

        /**
         * @brief Destroy the Keyboard object
         */
        ~Keyboard() = default;

        /**
         * @brief Delete copy constructor and assignment operator
         */
        Keyboard(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;

    public:
        /**
         * @brief Get the singleton instance of the Keyboard class.
         *
         * This function provides access to the singleton instance of the
         * Keyboard class using Meyer's singleton pattern.
         *
         * @return Reference to the singleton instance of the Keyboard class.
         */
        static Keyboard& getInstance();

        /**
         * @brief Registers a keyboard action.
         *
         * This function registers an action related to keyboard input, e.g.
         * pressing or releasing a specific key.
         *
         * @param key The keycode representing the key which fired the event.
         * @param action The action that triggered the event.
         */
        void registerAction(int key, int action);

        /**
         * @brief Checks if a key is currently being pressed down.
         *
         * @param key The keycode representing the key to check.
         * @return True if the key is being held down, false otherwise.
         */
        bool isKeyDown(int key) const;

        /**
         * @brief Checks if a key has been pressed.
         *
         * @param key The keycode representing the key to check.
         * @return True if the key has been pressed, false otherwise.
         */
        bool isKeyPressed(int key);
};
}  // namespace Obelisk

#endif  // KEYBOARD_H