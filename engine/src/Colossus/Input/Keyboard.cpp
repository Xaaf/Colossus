#include "Colossus/Input/Keyboard.h"
#include <algorithm>

using namespace Colossus;

Keyboard* Keyboard::instance = nullptr;

bool keys[GLFW_KEY_LAST];
std::vector<int> pressed_keys;

Keyboard::Keyboard() = default;
Keyboard::~Keyboard() = default;

Keyboard* Keyboard::getInstance() {
    if (instance == nullptr) {
        instance = new Keyboard();
    }

    return instance;
}

void Keyboard::callback(GLFWwindow* window, int key, int scancode, int action,
                        int mods) {
    keys[key] = action != GLFW_RELEASE;

    auto it = std::find(pressed_keys.begin(), pressed_keys.end(), key);
    if (action == GLFW_RELEASE && it != pressed_keys.end()) {
        pressed_keys.erase(it);
    }
}

bool Keyboard::isKeyDown(int key) { return keys[key]; }

bool Keyboard::isKeyPressed(int key) {
    if (!keys[key]) return false;

    auto it = std::find(pressed_keys.begin(), pressed_keys.end(), key);
    if (it != pressed_keys.end()) {
        return false;
    }

    pressed_keys.push_back(key);
    return true;
}
