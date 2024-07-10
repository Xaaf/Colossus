#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/vec3.hpp>

namespace Colossus {
class Transform {
    public:
        glm::vec3 position;
        glm::vec3 rotation;

        void move(glm::vec3 move);
        void rotate(glm::vec3 rot);

        static Transform empty() {
            Transform trans{};
            trans.position = glm::vec3(0, 0, 0);
            trans.rotation = glm::vec3(0, 0, 0);

            return trans;
        }
};
}  // namespace Colossus

#endif  // TRANSFORM_H
