#pragma once

#include <stb_image.h>
#include "ObeliskPCH.h"

namespace Obelisk {
class OBELISK_API Texture {
    private:
        unsigned int m_TextureID;

    public:
        Texture() = default;
        Texture(const std::string& path);
        ~Texture();

        void Bind(unsigned int textureSlot = 0) const;
};
}  // namespace Obelisk