#pragma once

#include "ObeliskPCH.h"
#include <stb_image.h>
#include "Obelisk/Core/AssetManager.h"

namespace Obelisk {

/**
 * @brief OpenGL texture wrapper for loading and managing 2D textures.
 *
 * The Texture class provides a convenient interface for loading image files
 * and creating OpenGL textures. It supports common image formats (PNG, JPG,
 * BMP, TGA) through the stb_image library and automatically handles OpenGL
 * texture creation, parameter setting, and resource cleanup.
 *
 * Key features:
 * - Automatic image loading from asset files
 * - Support for multiple image formats via stb_image
 * - OpenGL texture creation with sensible defaults
 * - RAII resource management
 * - Texture unit binding for multi-texturing
 * - Validation methods for error checking
 *
 * @example
 * ```cpp
 * // Load texture from assets directory
 * Texture playerTexture("textures/player.png");
 *
 * if (playerTexture.IsValid()) {
 *     // Bind to texture unit 0 for rendering
 *     playerTexture.Bind(0);
 *
 *     // Set shader uniform for texture sampler
 *     shader.SetInt("texture0", 0);
 *
 *     // Render geometry...
 * }
 * ```
 */
class OBELISK_API Texture {
    private:
        unsigned int
            m_TextureID;  ///< OpenGL texture ID (0 indicates invalid texture)

    public:
        /**
         * @brief Default constructor creating an invalid texture.
         *
         * Creates a texture object without loading any image data.
         * Use the parameterized constructor or load a texture manually
         * to create a usable texture.
         */
        Texture() = default;

        /**
         * @brief Load a texture from an image file.
         *
         * Loads an image file using stb_image, creates an OpenGL texture,
         * and configures appropriate texture parameters. Supports common
         * image formats including PNG, JPG, BMP, and TGA.
         *
         * The texture is created with the following OpenGL parameters:
         * - Wrap mode: GL_REPEAT for both S and T coordinates
         * - Filtering: GL_LINEAR for both minification and magnification
         * - Mipmaps: Automatically generated for better quality at distance
         *
         * @param path Relative path to the image file (e.g.,
         * "textures/player.png")
         *
         * @note Uses AssetManager for reliable file path resolution
         * @note Logs detailed error information if loading fails
         * @note Automatically handles different channel counts (RGB/RGBA)
         */
        Texture(const std::string& path);

        /**
         * @brief Destructor that cleans up OpenGL resources.
         *
         * Automatically deletes the OpenGL texture to prevent resource leaks.
         * Safe to call even if the texture was not successfully created.
         */
        ~Texture();

        /**
         * @brief Bind the texture to a specific texture unit for rendering.
         *
         * Activates the specified texture unit and binds this texture to it.
         * The texture will remain bound to this unit until another texture
         * is bound to the same unit or the texture is explicitly unbound.
         *
         * @param textureSlot Texture unit to bind to (0-31, typically)
         *
         * @example
         * ```cpp
         * texture1.Bind(0);  // Bind to texture unit 0
         * texture2.Bind(1);  // Bind to texture unit 1
         *
         * // Set shader uniforms to match
         * shader.SetInt("texture0", 0);
         * shader.SetInt("texture1", 1);
         * ```
         */
        void Bind(unsigned int textureSlot = 0) const;

        /**
         * @brief Check if the texture was loaded successfully.
         *
         * Returns whether the texture has a valid OpenGL texture ID,
         * indicating that the image was loaded and the texture was
         * created successfully.
         *
         * @return true if texture is valid and ready for use
         * @return false if texture loading failed or texture is uninitialized
         */
        bool IsValid() const { return m_TextureID != 0; }

        /**
         * @brief Get the OpenGL texture ID.
         *
         * Returns the underlying OpenGL texture identifier for advanced
         * operations or debugging. A value of 0 indicates an invalid texture.
         *
         * @return The OpenGL texture ID, or 0 if the texture is invalid
         */
        unsigned int GetID() const { return m_TextureID; }
};

}  // namespace Obelisk