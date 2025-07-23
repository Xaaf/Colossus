#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
class OBELISK_API Transform {
        glm::vec3 Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

        glm::mat4 GetModelMatrix() const;
};
}  // namespace Obelisk