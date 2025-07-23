#include "Obelisk/Components/Transform.h"

namespace Obelisk {
glm::mat4 Transform::GetModelMatrix() const {
    if (m_MatrixDirty) {
        // Dirty matrix, so start from scratch
        m_CachedModelMatrix = glm::mat4(1.0f);

        m_CachedModelMatrix = glm::translate(m_CachedModelMatrix, m_Position);
        // Rotate Y -> X -> Z to prevent "gimbal lock"
        m_CachedModelMatrix =
            glm::rotate(m_CachedModelMatrix, glm::radians(m_Rotation.y),
                        glm::vec3(0, 1, 0));
        m_CachedModelMatrix =
            glm::rotate(m_CachedModelMatrix, glm::radians(m_Rotation.x),
                        glm::vec3(1, 0, 0));
        m_CachedModelMatrix =
            glm::rotate(m_CachedModelMatrix, glm::radians(m_Rotation.z),
                        glm::vec3(0, 0, 1));
        m_CachedModelMatrix = glm::scale(m_CachedModelMatrix, m_Scale);

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
    m_Rotation += eulerDelta;
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

glm::vec3 Transform::GetForward() const {
    return glm::normalize(glm::vec3(GetModelMatrix() * glm::vec4(0, 0, -1, 0)));
}

glm::vec3 Transform::GetRight() const {
    return glm::normalize(glm::vec3(GetModelMatrix() * glm::vec4(1, 0, 0, 0)));
}

glm::vec3 Transform::GetUp() const {
    return glm::normalize(glm::vec3(GetModelMatrix() * glm::vec4(0, 1, 0, 0)));
}
}  // namespace Obelisk