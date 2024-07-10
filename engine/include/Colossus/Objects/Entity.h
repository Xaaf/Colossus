#ifndef ENTITY_H
#define ENTITY_H
#include "Colossus/Render/Mesh.h"
#include "Colossus/Transform.h"
#include "cspch.h"

namespace Colossus {
class Entity {
    private:
        Mesh mesh;

    public:
        Transform transform = Transform::empty();

        Entity(Mesh mesh);
        Entity(Mesh mesh, glm::vec3 position);
        Entity(Mesh mesh, glm::vec3 position, glm::vec3 rotation);

        Mesh getMesh() { return mesh; }
};
}  // namespace Colossus

#endif  // ENTITY_H
