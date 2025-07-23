#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {

/**
 * @brief Vertex data structure containing position, color, and texture
 * coordinates.
 *
 * Defines the layout of vertex data used throughout the rendering system.
 * Each vertex contains 3D position, RGB color, and 2D texture coordinates,
 * providing enough information for basic 3D rendering with texturing and
 * per-vertex coloring.
 */
struct OBELISK_API Vertex {
        glm::vec3 Position;       ///< 3D position in local space
        glm::vec3 Color;          ///< RGB color values (0.0 to 1.0 range)
        glm::vec2 TextureCoords;  ///< UV texture coordinates (typically 0.0
                                  ///< to 1.0 range)
};

/**
 * @brief OpenGL mesh class for managing vertex data and rendering geometry.
 *
 * The Mesh class encapsulates OpenGL Vertex Array Objects (VAO), Vertex Buffer
 * Objects (VBO), and Element Buffer Objects (EBO) to efficiently store and
 * render 3D geometry. It provides a high-level interface for creating meshes
 * from vertex and index data, with automatic OpenGL resource management.
 *
 * Key features:
 * - Automatic VAO/VBO/EBO creation and management
 * - Support for indexed rendering for memory efficiency
 * - RAII resource cleanup to prevent memory leaks
 * - Vertex data layout compatible with standard shaders
 * - Unique mesh ID system for debugging and identification
 *
 * @note The mesh assumes a specific vertex layout (position, color, texture
 * coords)
 * @note Uses 32-bit indices for element arrays
 *
 * @example
 * ```cpp
 * // Define vertices for a triangle
 * std::vector<Vertex> vertices = {
 *     {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
 *     {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
 *     {{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}
 * };
 *
 * std::vector<unsigned int> indices = {0, 1, 2};
 *
 * // Create mesh and render
 * Mesh triangle(vertices, indices);
 * triangle.Bind();
 * glDrawElements(GL_TRIANGLES, triangle.GetNumberOfIndices(), GL_UNSIGNED_INT,
 * 0);
 * ```
 */
class OBELISK_API Mesh {
    private:
        unsigned int m_VAO = 0;  ///< OpenGL Vertex Array Object ID
        unsigned int m_VBO = 0;  ///< OpenGL Vertex Buffer Object ID
        unsigned int m_EBO = 0;  ///< OpenGL Element Buffer Object ID

        int m_NumVertices = 0;  ///< Number of vertices in this mesh
        int m_NumIndices = 0;   ///< Number of indices in this mesh

        uint32_t m_MeshID = -1;  ///< Unique identifier for this mesh instance
        static uint32_t
            s_NextMeshID;  ///< Static counter for generating unique mesh IDs

    public:
        /**
         * @brief Default constructor creating an empty mesh.
         *
         * Creates a mesh object without any vertex data or OpenGL resources.
         * Use the parameterized constructor or load geometry data separately
         * to create a usable mesh.
         */
        Mesh() = default;

        /**
         * @brief Create a mesh from vertex and index data.
         *
         * Constructs a complete mesh by creating OpenGL vertex array, vertex
         * buffer, and element buffer objects. The vertex data is uploaded to
         * GPU memory and configured with the appropriate vertex attribute
         * layout.
         *
         * Vertex attribute layout:
         * - Location 0: Position (vec3) - 3 floats at offset 0
         * - Location 1: Color (vec3) - 3 floats at offset 12 bytes
         * - Location 2: Texture Coordinates (vec2) - 2 floats at offset 24
         * bytes
         *
         * @param vertices Vector of vertex data to upload to the GPU
         * @param indices Vector of indices for indexed rendering (reduces
         * memory usage)
         *
         * @note The mesh takes ownership of the data and uploads it to GPU
         * memory
         * @note Indices should reference valid vertex array positions
         */
        Mesh(std::vector<Vertex> const& vertices,
             std::vector<unsigned int> const& indices);

        /**
         * @brief Destructor that cleans up OpenGL resources.
         *
         * Automatically deletes the VAO, VBO, and EBO to prevent resource
         * leaks. Safe to call even if the mesh was not successfully created.
         */
        ~Mesh();

        /**
         * @brief Bind this mesh's VAO for rendering.
         *
         * Makes this mesh's vertex array object the active VAO, setting up
         * all vertex attributes and buffer bindings for subsequent draw calls.
         * The mesh remains bound until another mesh is bound or Unbind() is
         * called.
         */
        void Bind() const;

        /**
         * @brief Unbind the currently active vertex array object.
         *
         * Unbinds any currently bound VAO by binding VAO 0. This is typically
         * called after rendering to clean up OpenGL state, though it's not
         * strictly necessary in most rendering scenarios.
         */
        static void Unbind();

        /**
         * @brief Get the number of vertices in this mesh.
         *
         * @return Number of vertices that were used to create this mesh
         */
        [[nodiscard]] int GetNumberOfVertices() const { return m_NumVertices; };

        /**
         * @brief Get the number of indices in this mesh.
         *
         * @return Number of indices in the element buffer, used for
         * glDrawElements calls
         */
        [[nodiscard]] int GetNumberOfIndices() const { return m_NumIndices; };
};

}  // namespace Obelisk