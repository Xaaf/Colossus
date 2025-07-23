#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Components/Transform.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"
#include "Obelisk/Renderer/Texture.h"

namespace Obelisk {

/**
 * @brief Represents a renderable game object with transform, mesh, shader, and
 * texture.
 *
 * The Entity class is a fundamental building block of the engine's scene
 * system. It combines the essential components needed for rendering: a 3D
 * transformation, geometric mesh data, shader program, and texture. This design
 * provides a simple but flexible foundation for game objects that can be
 * positioned, rendered, and manipulated in 3D space.
 *
 * Key components:
 * - Transform: Position, rotation, and scale in 3D space
 * - Mesh: Vertex data and geometry information
 * - Shader: GPU program for rendering the entity
 * - Texture: Surface appearance and material properties
 *
 * @note This is a simplified entity design focused on rendering. More complex
 *       entity-component systems would separate these concerns into individual
 * components.
 *
 * @example
 * ```cpp
 * // Create shared resources
 * auto cubeMesh = std::make_shared<Mesh>(cubeVertices);
 * auto basicShader = std::make_shared<Shader>("basic.vert", "basic.frag");
 * auto brickTexture = std::make_shared<Texture>("textures/brick.jpg");
 *
 * // Create entity with all components
 * Entity cube(cubeMesh, basicShader, brickTexture);
 *
 * // Transform the entity
 * cube.GetTransform().SetPosition(glm::vec3(2.0f, 0.0f, -5.0f));
 * cube.GetTransform().SetRotation(glm::vec3(0.0f, 45.0f, 0.0f));
 *
 * // Render the entity
 * cube.Draw();
 * ```
 */
class OBELISK_API Entity {
    private:
        std::shared_ptr<Mesh>
            m_Mesh;  ///< Geometric mesh data (shared resource)
        std::shared_ptr<Shader>
            m_Shader;  ///< GPU shader program (shared resource)
        std::shared_ptr<Texture>
            m_Texture;  ///< Surface texture (shared resource)

        Transform
            m_Transform;  ///< 3D transformation (position, rotation, scale)

    public:
        /**
         * @brief Default constructor creating an entity with no components.
         *
         * Creates an entity with an identity transform but no mesh, shader, or
         * texture. Components must be set individually using the setter methods
         * before the entity can be rendered.
         */
        Entity();

        /**
         * @brief Create an entity with all rendering components.
         *
         * Constructs a complete entity ready for rendering with the specified
         * mesh, shader, and texture. The transform is initialized to identity
         * (position at origin, no rotation, unit scale).
         *
         * @param mesh Shared pointer to the mesh geometry
         * @param shader Shared pointer to the shader program
         * @param texture Shared pointer to the surface texture
         *
         * @note Using shared pointers allows multiple entities to share the
         * same resources, reducing memory usage and improving performance
         */
        Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader,
               std::shared_ptr<Texture> texture);

        /**
         * @brief Set the mesh component for this entity.
         *
         * @param mesh Shared pointer to the new mesh geometry
         */
        void SetMesh(std::shared_ptr<Mesh> mesh);

        /**
         * @brief Set the shader component for this entity.
         *
         * @param shader Shared pointer to the new shader program
         */
        void SetShader(std::shared_ptr<Shader> shader);

        /**
         * @brief Set the texture component for this entity.
         *
         * @param texture Shared pointer to the new surface texture
         */
        void SetTexture(std::shared_ptr<Texture> texture);

        /**
         * @brief Get a reference to the entity's transform component.
         *
         * Provides direct access to the transform for modifying position,
         * rotation, and scale. The returned reference allows both reading
         * and writing of transform properties.
         *
         * @return Reference to the entity's Transform component
         */
        Transform& GetTransform() { return m_Transform; }

        /**
         * @brief Get the entity's mesh component.
         *
         * @return Shared pointer to the mesh, or nullptr if no mesh is set
         */
        std::shared_ptr<Mesh> GetMesh() const;

        /**
         * @brief Get the entity's shader component.
         *
         * @return Shared pointer to the shader, or nullptr if no shader is set
         */
        std::shared_ptr<Shader> GetShader() const;

        /**
         * @brief Get the entity's texture component.
         *
         * @return Shared pointer to the texture, or nullptr if no texture is
         * set
         */
        std::shared_ptr<Texture> GetTexture() const;

        /**
         * @brief Render this entity to the current framebuffer.
         *
         * Performs a complete rendering operation for this entity:
         * 1. Binds the shader program
         * 2. Sets transform matrices as uniforms
         * 3. Binds the texture to texture unit 0
         * 4. Draws the mesh geometry
         *
         * The entity must have valid mesh, shader, and texture components
         * for rendering to succeed.
         *
         * @note Assumes appropriate OpenGL state has been set up (viewport,
         * etc.)
         * @note Uses the current projection and view matrices from the
         * rendering context
         */
        void Draw() const;
};

}  // namespace Obelisk