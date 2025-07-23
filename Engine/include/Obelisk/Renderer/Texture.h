#pragma once

#include "ObeliskPCH.h"
#include <stb_image.h>
#include "Obelisk/Core/AssetManager.h"


namespace Obelisk {
class OBELISK_API Texture {
    private:
        unsigned int m_TextureID;

    public:
        Texture() = default;
        Texture(const std::string& path);
        ~Texture();

        void Bind(unsigned int textureSlot = 0) const;

        /**
         * @brief Check if the texture was loaded successfully
         * @return True if texture is valid, false otherwise
         */
        bool IsValid() const { return m_TextureID != 0; }

        /**
         * @brief Get the OpenGL texture ID
         * @return The texture ID, or 0 if invalid
         */
        unsigned int GetID() const { return m_TextureID; }
};
}  // namespace Obelisk