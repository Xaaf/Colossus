#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "cspch.h"

namespace Colossus {
class Keyboard {
    private:
        static Keyboard* instance;

    private:
        Keyboard();
        ~Keyboard();

    public:
        static Keyboard* getInstance();
        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static bool isKeyDown(int key);
        static bool isKeyPressed(int key);
};
}  // namespace Colossus

#endif  // KEYBOARD_H
