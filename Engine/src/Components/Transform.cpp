#include "Obelisk/Components/Transform.h"

namespace Obelisk {
glm::mat4 Transform::GetModelMatrix() const {
    if (m_MatrixDirty) {
        // Build transformation matrix using TRS order (Scale -> Rotate ->
        // Translate)
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);
        glm::mat4 rotation = glm::mat4_cast(m_Rotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

        // Combine transformations: T * R * S
        m_CachedModelMatrix = translation * rotation * scale;

        m_MatrixDirty = false;
    }

    return m_CachedModelMatrix;
}

glm::mat4 Transform::GetInverseModelMatrix() const {
    return glm::inverse(GetModelMatrix());
}

void Transform::Translate(const glm::vec3& delta) {
    m_Position += delta;
    m_MatrixDirty = true;
}

void Transform::Rotate(const glm::vec3& eulerDelta) {
    // Convert Euler angles to quaternion and apply as relative rotation
    glm::quat deltaRotation = glm::quat(glm::radians(eulerDelta));
    m_Rotation = m_Rotation * deltaRotation;
    m_MatrixDirty = true;
}

void Transform::Scale(const glm::vec3& scaleFactor) {
    m_Scale *= scaleFactor;
    m_MatrixDirty = true;
}

void Transform::Scale(float scaleFactor) {
    m_Scale *= glm::vec3(scaleFactor);
    m_MatrixDirty = true;
}

}  // namespace Obelisk