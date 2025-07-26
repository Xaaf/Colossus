#include "Obelisk/Input/Mouse.h"
#include <algorithm>
#include "Obelisk/Logging/Log.h"

namespace Obelisk {

// Static member definitions
std::array<bool, OB_MOUSE_BUTTON_LAST + 1> Mouse::s_Buttons{};
std::vector<int> Mouse::s_PreviousButtons{};
glm::vec2 Mouse::s_Position{0.0f, 0.0f};

void Mouse::RegisterAction(int button, int action) {
    // Bounds checking
    if (button < 0 || button > OB_MOUSE_BUTTON_LAST) {
        LOG_WARN("Invalid mouse button: {}", button);
        return;
    }

    s_Buttons[button] = action != OB_RELEASE;

    auto it =
        std::find(s_PreviousButtons.begin(), s_PreviousButtons.end(), button);
    if (action == OB_RELEASE && it != s_PreviousButtons.end()) {
        // Button was released, remove from previous buttons
        s_PreviousButtons.erase(it);
        LOG_INFO("Mouse button {} released, removed from previous buttons",
                 button);
    }
}

void Mouse::RegisterMove(double newX, double newY) {
    s_Position.x = static_cast<float>(newX);
    s_Position.y = static_cast<float>(newY);
}

bool Mouse::IsButtonDown(int button) {
    if (button < 0 || button > OB_MOUSE_BUTTON_LAST) {
        return false;
    }
    return s_Buttons[button];
}

bool Mouse::IsButtonPressed(int button) {
    if (button < 0 || button > OB_MOUSE_BUTTON_LAST) {
        return false;
    }

    auto it =
        std::find(s_PreviousButtons.begin(), s_PreviousButtons.end(), button);
    if (it != s_PreviousButtons.end()) {
        // Button was previously pressed, but not this frame
        return false;
    }

    s_PreviousButtons.push_back(button);
    return true;
}

glm::vec2 Mouse::GetMousePosition() { return s_Position; }
}  // namespace Obelisk