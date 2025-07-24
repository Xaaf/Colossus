#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Components/Transform.h"

namespace Obelisk {

/**
 * @brief Camera class for handling view and projection transformations
 *
 * Provides a complete camera system with:
 * - Perspective and orthographic projections
 * - View matrix calculation based on transform
 * - Camera movement and rotation controls
 * - Automatic aspect ratio handling
 */
class OBELISK_API Camera {
    public:
        /**
         * @brief Camera projection types
         */
        enum class ProjectionType {
            Perspective,  ///< 3D perspective projection
            Orthographic  ///< 2D/3D orthographic projection
        };

    private:
        Transform
            m_Transform;  ///< Camera's transform (position, rotation, scale)

        // Projection settings
        ProjectionType m_ProjectionType = ProjectionType::Perspective;
        float m_FOV = 45.0f;        ///< Field of view in degrees (perspective)
        float m_NearPlane = 0.1f;   ///< Near clipping plane distance
        float m_FarPlane = 100.0f;  ///< Far clipping plane distance
        float m_AspectRatio = 16.0f / 9.0f;  ///< Aspect ratio (width/height)

        // Orthographic settings
        float m_OrthographicSize = 10.0f;  ///< Half-height of orthographic view

        // Cached matrices
        mutable glm::mat4 m_ProjectionMatrix =
            glm::mat4(1.0f);  ///< Cached projection matrix
        mutable glm::mat4 m_ViewMatrix =
            glm::mat4(1.0f);  ///< Cached view matrix
        mutable bool m_ProjectionDirty =
            true;  ///< Flag indicating projection matrix needs recalculation
        mutable bool m_ViewDirty =
            true;  ///< Flag indicating view matrix needs recalculation

    public:
        /**
         * @brief Default constructor
         */
        Camera();

        /**
         * @brief Constructor with custom settings
         * @param fov Field of view in degrees
         * @param aspectRatio Aspect ratio (width/height)
         * @param nearPlane Near clipping plane distance
         * @param farPlane Far clipping plane distance
         */
        Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

        // === Transform Access ===

        /**
         * @brief Get the camera's transform component
         * @return Reference to the transform
         */
        Transform& GetTransform() {
            MarkViewDirty();
            return m_Transform;
        }

        /**
         * @brief Get the camera's transform component (const)
         * @return Const reference to the transform
         */
        const Transform& GetTransform() const { return m_Transform; }

        // === Position Controls ===

        /**
         * @brief Set camera position
         * @param position New position
         */
        void SetPosition(const glm::vec3& position);

        /**
         * @brief Get camera position
         * @return Current position
         */
        glm::vec3 GetPosition() const { return m_Transform.GetPosition(); }

        /**
         * @brief Move camera by offset
         * @param offset Movement offset
         */
        void Move(const glm::vec3& offset);

        // === Rotation Controls ===

        /**
         * @brief Set camera rotation using Euler angles
         * @param rotation Euler angles in degrees (pitch, yaw, roll)
         */
        void SetRotation(const glm::vec3& rotation);

        /**
         * @brief Set camera rotation using quaternion
         * @param rotation Quaternion rotation
         */
        void SetRotation(const glm::quat& rotation);

        /**
         * @brief Get camera rotation as Euler angles
         * @return Euler angles in degrees
         */
        glm::vec3 GetRotation() const { return m_Transform.GetRotation(); }

        /**
         * @brief Get camera rotation as quaternion
         * @return Quaternion rotation
         */
        glm::quat GetRotationQuaternion() const {
            return m_Transform.GetRotationQuat();
        }

        /**
         * @brief Rotate camera by Euler angles
         * @param rotation Rotation offset in degrees
         */
        void Rotate(const glm::vec3& rotation);

        /**
         * @brief Make camera look at a target position
         * @param target Target position to look at
         * @param up Up vector (default: world up)
         */
        void LookAt(const glm::vec3& target,
                    const glm::vec3& up = glm::vec3(0, 1, 0));

        // === Direction Vectors ===

        /**
         * @brief Get camera's forward direction
         * @return Forward vector
         */
        glm::vec3 GetForward() const { return m_Transform.GetForward(); }

        /**
         * @brief Get camera's right direction
         * @return Right vector
         */
        glm::vec3 GetRight() const { return m_Transform.GetRight(); }

        /**
         * @brief Get camera's up direction
         * @return Up vector
         */
        glm::vec3 GetUp() const { return m_Transform.GetUp(); }

        // === Projection Settings ===

        /**
         * @brief Set projection type
         * @param type Projection type (perspective or orthographic)
         */
        void SetProjectionType(ProjectionType type);

        /**
         * @brief Get projection type
         * @return Current projection type
         */
        ProjectionType GetProjectionType() const { return m_ProjectionType; }

        /**
         * @brief Set field of view (perspective only)
         * @param fov Field of view in degrees
         */
        void SetFieldOfView(float fov);

        /**
         * @brief Get field of view
         * @return Field of view in degrees
         */
        float GetFieldOfView() const { return m_FOV; }

        /**
         * @brief Set aspect ratio
         * @param aspectRatio Aspect ratio (width/height)
         */
        void SetAspectRatio(float aspectRatio);

        /**
         * @brief Get aspect ratio
         * @return Current aspect ratio
         */
        float GetAspectRatio() const { return m_AspectRatio; }

        /**
         * @brief Set clipping planes
         * @param nearPlane Near clipping plane distance
         * @param farPlane Far clipping plane distance
         */
        void SetClippingPlanes(float nearPlane, float farPlane);

        /**
         * @brief Get near clipping plane distance
         * @return Near plane distance
         */
        float GetNearPlane() const { return m_NearPlane; }

        /**
         * @brief Get far clipping plane distance
         * @return Far plane distance
         */
        float GetFarPlane() const { return m_FarPlane; }

        /**
         * @brief Set orthographic size (orthographic only)
         * @param size Half-height of orthographic view
         */
        void SetOrthographicSize(float size);

        /**
         * @brief Get orthographic size
         * @return Orthographic size
         */
        float GetOrthographicSize() const { return m_OrthographicSize; }

        // === Matrix Access ===

        /**
         * @brief Get view matrix
         * @return View matrix (world to camera space)
         */
        const glm::mat4& GetViewMatrix() const;

        /**
         * @brief Get projection matrix
         * @return Projection matrix (camera to clip space)
         */
        const glm::mat4& GetProjectionMatrix() const;

        /**
         * @brief Get view-projection matrix
         * @return Combined view and projection matrix
         */
        glm::mat4 GetViewProjectionMatrix() const;

        // === Utility Methods ===

        /**
         * @brief Convert screen coordinates to world ray
         * @param screenPos Screen position (normalized device coordinates)
         * @return Ray direction in world space
         */
        glm::vec3 ScreenToWorldRay(const glm::vec2& screenPos) const;

        /**
         * @brief Convert world position to screen coordinates
         * @param worldPos World position
         * @return Screen position (normalized device coordinates)
         */
        glm::vec2 WorldToScreen(const glm::vec3& worldPos) const;

    private:
        /**
         * @brief Mark projection matrix as dirty
         */
        void MarkProjectionDirty() const { m_ProjectionDirty = true; }

        /**
         * @brief Mark view matrix as dirty
         */
        void MarkViewDirty() const { m_ViewDirty = true; }

        /**
         * @brief Recalculate projection matrix if dirty
         */
        void UpdateProjectionMatrix() const;

        /**
         * @brief Recalculate view matrix if dirty
         */
        void UpdateViewMatrix() const;
};

}  // namespace Obelisk