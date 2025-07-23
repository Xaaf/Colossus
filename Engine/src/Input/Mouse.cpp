#include "Obelisk/Input/Mouse.h"
#include <algorithm>

namespace Obelisk {

Mouse& Mouse::getInstance() {
    static Mouse instance;
    return instance;
}

void Mouse::registerAction(int button, int action) {
    // Bounds checking
    if (button < 0 || button > CS_MOUSE_BUTTON_LAST) {
        LOG_WARN("Invalid mouse button: " << button);
        return;
    }
    m_Buttons[button] = action != CS_RELEASE;

    auto it =
        std::find(m_PressedButtons.begin(), m_PressedButtons.end(), button);
    if (action == CS_RELEASE && it != m_PressedButtons.end()) {
        m_PressedButtons.erase(it);
    }
}

void Mouse::registerMove(double newX, double newY) {
    m_Position.x = static_cast<float>(newX);
    m_Position.y = static_cast<float>(newY);
}

bool Mouse::isButtonDown(int button) const {
    if (button < 0 || button > CS_MOUSE_BUTTON_LAST) {
        return false;
    }
    return m_Buttons[button];
}

bool Mouse::isButtonPressed(int button) {
    if (button < 0 || button > CS_MOUSE_BUTTON_LAST) {
        return false;
    }

    if (!m_Buttons[button]) return false;

    auto it =
        std::find(m_PressedButtons.begin(), m_PressedButtons.end(), button);
    if (it != m_PressedButtons.end()) {
        return false;
    }

    m_PressedButtons.push_back(button);
    return true;
}

glm::vec2 Mouse::getMousePosition() const { return m_Position; }
}  // namespace Obelisk