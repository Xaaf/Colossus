#include "Obelisk/Input/Keyboard.h"
#include <algorithm>

namespace Obelisk {

Keyboard& Keyboard::getInstance() {
    static Keyboard instance;
    return instance;
}

void Keyboard::registerAction(int key, int action) {
    // Bounds checking
    if (key < 0 || key > CS_KEY_LAST) {
        LOG_WARN("Invalid key: {}", key);
        return;
    }

    m_Keys[key] = action != CS_RELEASE;

    auto it = std::find(m_PressedKeys.begin(), m_PressedKeys.end(), key);
    if (action == CS_RELEASE && it != m_PressedKeys.end()) {
        m_PressedKeys.erase(it);
    }
}

bool Keyboard::isKeyDown(int key) const {
    if (key < 0 || key > CS_KEY_LAST) {
        return false;
    }
    return m_Keys[key];
}

bool Keyboard::isKeyPressed(int key) {
    if (key < 0 || key > CS_KEY_LAST) {
        return false;
    }

    if (!m_Keys[key]) return false;

    auto it = std::find(m_PressedKeys.begin(), m_PressedKeys.end(), key);
    if (it != m_PressedKeys.end()) {
        return false;
    }

    m_PressedKeys.push_back(key);
    return true;
}
}  // namespace Obelisk