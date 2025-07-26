#include "Obelisk/Input/Keyboard.h"
#include <algorithm>
#include "Obelisk/Logging/Log.h"

namespace Obelisk {

// Static member definitions
std::array<bool, OB_KEY_LAST + 1> Keyboard::s_Keys{};
std::vector<int> Keyboard::s_PreviousKeys{};

void Keyboard::RegisterAction(int key, int action) {
    // Bounds checking
    if (key < 0 || key > OB_KEY_LAST) {
        LOG_WARN("Invalid key: {}", key);
        return;
    }

    s_Keys[key] = action != OB_RELEASE;

    auto it = std::find(s_PreviousKeys.begin(), s_PreviousKeys.end(), key);
    if (action == OB_RELEASE && it != s_PreviousKeys.end()) {
        // Key was released, remove from previous keys
        s_PreviousKeys.erase(it);
        LOG_INFO("Key {} released, removed from previous keys", key);
    }
}

bool Keyboard::IsKeyDown(int key) {
    if (key < 0 || key > OB_KEY_LAST) {
        LOG_WARN("Invalid key: {}", key);
        return false;
    }

    return s_Keys[key];
}

bool Keyboard::IsKeyPressed(int key) {
    if (key < 0 || key > OB_KEY_LAST) {
        LOG_WARN("Invalid key: {}", key);
        return false;
    }

    auto it = std::find(s_PreviousKeys.begin(), s_PreviousKeys.end(), key);
    if (it != s_PreviousKeys.end()) {
        // Key was previously pressed, but not this frame
        return false;
    }

    s_PreviousKeys.push_back(key);
    return true;
}
}  // namespace Obelisk