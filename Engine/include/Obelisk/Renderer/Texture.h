#pragma once

#include "ObeliskPCH.h"

#include <stb_image.h>

namespace Obelisk {
class OBELISK_API Texture {
    private:
        unsigned int m_TextureID;

    public:
        Texture() = default;
        Texture(const std::string& path);
        ~Texture() = default;

        void Bind(unsigned int textureSlot = 0) const;
};
}