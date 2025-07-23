#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
class OBELISK_API Transform {
    private:
        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 m_Scale = {1.0f, 1.0f, 1.0f};

        mutable glm::mat4 m_CachedModelMatrix = glm::mat4(1.0f);
        mutable bool m_MatrixDirty = false;

    public:
        glm::mat4 GetModelMatrix() const;
        glm::mat4 GetInverseModelMatrix() const;

        glm::vec3 GetPosition() const { return m_Position; }
        glm::vec3 GetRotation() const { return m_Rotation; }
        glm::vec3 GetScale() const { return m_Scale; }

        void SetPosition(glm::vec3 position) {
            m_Position = position;
            m_MatrixDirty = true;
        }
        void SetPosition(float x, float y, float z) {
            m_Position = glm::vec3(x, y, z);
            m_MatrixDirty = true;
        }

        void SetRotation(glm::vec3 rotation) {
            m_Rotation = rotation;
            m_MatrixDirty = true;
        }
        void SetRotation(float pitch, float yaw, float roll) {
            m_Rotation = glm::vec3(pitch, yaw, roll);
            m_MatrixDirty = true;
        }

        void SetScale(glm::vec3 scale) {
            m_Scale = scale;
            m_MatrixDirty = true;
        }
        void SetScale(float x, float y, float z) {
            m_Scale = glm::vec3(x, y, z);
            m_MatrixDirty = true;
        }

        void Translate(const glm::vec3& delta);
        void Rotate(const glm::vec3& eulerDelta);
        void Scale(const glm::vec3& scaleFactor);
        void Scale(float scaleFactor);

        glm::vec3 GetForward() const;
        glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;
};
}  // namespace Obelisk