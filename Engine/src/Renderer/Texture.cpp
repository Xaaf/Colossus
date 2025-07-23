#include "Obelisk/Renderer/Texture.h"

namespace Obelisk {
Texture::Texture(const std::string& path) {
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    // Use AssetManager to get the full path
    std::filesystem::path fullPath =
        AssetManager::GetAssetPath("textures/" + path);

    // Check if asset exists before trying to load
    if (!AssetManager::AssetExists("textures/" + path)) {
        LOG_ERROR("Texture file not found: " << path);
        LOG_ERROR("Searched path: " << fullPath.string());
        LOG_ERROR(AssetManager::GetDebugInfo());
        m_TextureID = 0;  // Mark as invalid
        return;
    }

    unsigned char* data =
        stbi_load(fullPath.string().c_str(), &width, &height, &nrChannels, 0);

    if (!data) {
        LOG_ERROR("Failed to load texture: " << fullPath.string() << " - "
                                             << stbi_failure_reason());
        LOG_ERROR(AssetManager::GetDebugInfo());
        m_TextureID = 0;  // Mark as invalid
        return;
    }

    // Determine format based on number of channels
    GLenum format = GL_RGB;
    if (nrChannels == 1) {
        format = GL_RED;
    } else if (nrChannels == 3) {
        format = GL_RGB;
    } else if (nrChannels == 4) {
        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    LOG_TRACE("Successfully loaded texture: " << fullPath.string() << " ("
                                              << width << "x" << height << ", "
                                              << nrChannels << " channels)");
}

Texture::~Texture() {
    if (m_TextureID) {
        glDeleteTextures(1, &m_TextureID);
        LOG_TRACE("Texture with ID " << m_TextureID << " destroyed.");
        m_TextureID = 0;
    }
}

void Texture::Bind(unsigned int textureSlot) const {
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
}  // namespace Obelisk