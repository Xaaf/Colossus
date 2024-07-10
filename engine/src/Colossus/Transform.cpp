#include "Colossus/Transform.h"

using namespace Colossus;

void Transform::move(const glm::vec3 move) {
    position += move;
}

void Transform::rotate(const glm::vec3 rot) {
    rotation += rot;
}