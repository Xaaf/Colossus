#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ObeliskPCH.h"
#include <array>
#include <unordered_set>
#include "Obelisk/Input/InputCodes.h"

namespace Obelisk {
/**
 * @brief Manages keyboard input for the engine.
 *
 * Provides a static interface to handle keyboard events. It allows
 * registering per-key actions and the querying of said keys through their
 * respective static methods.
 */
class OBELISK_API Keyboard {
    private:
        /**
         * @brief Key states array
         */
        static std::array<bool, OB_KEY_LAST + 1> s_Keys;

        /**
         * @brief Keys that were previously pressed
         */
        static std::vector<int> s_PreviousKeys;

    public:
        /**
         * @brief Registers a keyboard action.
         *
         * This function registers an action related to keyboard input, e.g.
         * pressing or releasing a specific key.
         *
         * @param key The keycode representing the key which fired the event.
         * @param action The action that triggered the event.
         */
        static void RegisterAction(int key, int action);

        /**
         * @brief Checks if a key is currently being pressed down.
         *
         * @param key The keycode representing the key to check.
         * @return True if the key is being held down, false otherwise.
         */
        static bool IsKeyDown(int key);

        /**
         * @brief Checks if a key has been pressed this frame.
         *
         * @param key The keycode representing the key to check.
         * @return True if the key was just pressed this frame, false otherwise.
         */
        static bool IsKeyPressed(int key);

        /**
         * @brief Clears the just-pressed state for end of frame processing.
         * This should be called at the end of each frame.
         */
        static void EndFrame();
};
}  // namespace Obelisk

#endif  // KEYBOARD_H