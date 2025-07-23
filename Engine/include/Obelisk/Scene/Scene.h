#pragma once

#include "ObeliskPCH.h"
#include "Entity.h"


namespace Obelisk {

/**
 * @brief Container for managing entities and scene state.
 *
 * The Scene class represents a collection of entities that make up a particular
 * game state or level. It provides methods for adding entities and accessing
 * the complete entity list for systems that need to iterate over all entities
 * (such as rendering, physics, or game logic systems).
 *
 * Key responsibilities:
 * - Entity lifecycle management within the scene
 * - Providing access to entities for various game systems
 * - Serving as the organizational unit for different game states
 *
 * @note The Scene class does not own the Entity objects - it maintains pointers
 *       to entities that should be managed elsewhere (typically by an
 * EntityManager)
 *
 * @example
 * ```cpp
 * Scene gameScene;
 *
 * // Add entities to the scene
 * gameScene.AddEntity(player);
 * gameScene.AddEntity(enemy1);
 * gameScene.AddEntity(terrain);
 *
 * // Systems can iterate over all entities
 * for (Entity* entity : gameScene.GetEntities()) {
 *     // Process entity (update, render, etc.)
 * }
 * ```
 */
class OBELISK_API Scene {
    private:
        std::vector<Entity*>
            m_Entities;  ///< Collection of entities in this scene (not owned)

    public:
        /**
         * @brief Add an entity to the scene.
         *
         * Adds the specified entity to this scene's entity list, making it
         * available for processing by game systems. The scene does not take
         * ownership of the entity - the caller retains responsibility for
         * the entity's lifecycle.
         *
         * @param entity Pointer to the entity to add (must not be nullptr)
         *
         * @note Does not check for duplicate entities - the same entity
         *       can be added multiple times if called repeatedly
         * @note The entity should remain valid for the lifetime of the scene
         */
        void AddEntity(Entity* entity) { m_Entities.push_back(entity); }

        /**
         * @brief Get the list of all entities in the scene.
         *
         * Returns a reference to the internal entity vector, allowing systems
         * to iterate over all entities for processing. This enables various
         * game systems (rendering, physics, AI, etc.) to operate on all
         * entities in the scene.
         *
         * @return Reference to the vector containing all entities in the scene
         *
         * @note The returned reference remains valid until entities are added
         * or removed
         * @note Callers should not store long-term references to this vector
         */
        std::vector<Entity*>& GetEntities() { return m_Entities; }
};

}  // namespace Obelisk