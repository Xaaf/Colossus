#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {

/**
 * @brief Represents 3D transformation properties and matrix operations for
 * entities.
 *
 * The Transform class encapsulates position, rotation, and scale components
 * that define an object's transformation in 3D space. It provides convenient
 * methods for manipulating these properties and efficiently generates
 * transformation matrices for rendering and physics calculations.
 *
 * Key features:
 * - Position, rotation (Euler angles), and scale storage
 * - Lazy evaluation with matrix caching for performance
 * - Convenient setter methods with automatic cache invalidation
 * - Utility methods for common transformations (translate, rotate, scale)
 * - Directional vector calculations (forward, right, up)
 * - Both 4x4 transformation matrix and inverse matrix generation
 *
 * @note Rotation values are stored as Euler angles in degrees (pitch, yaw,
 * roll)
 * @note Matrix calculations are deferred until needed and cached for efficiency
 *
 * @example
 * ```cpp
 * Transform transform;
 *
 * // Set initial transform
 * transform.SetPosition(0.0f, 2.0f, -5.0f);
 * transform.SetRotation(0.0f, 45.0f, 0.0f);  // 45 degree Y rotation
 * transform.SetScale(2.0f, 1.0f, 2.0f);      // Scale X and Z by 2
 *
 * // Apply relative transformations
 * transform.Translate(glm::vec3(1.0f, 0.0f, 0.0f));  // Move right
 * transform.Rotate(glm::vec3(0.0f, 90.0f, 0.0f));    // Additional Y rotation
 *
 * // Get transformation matrix for rendering
 * glm::mat4 modelMatrix = transform.GetModelMatrix();
 * ```
 */
class OBELISK_API Transform {
    private:
        glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};  ///< World space position
        glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);  ///< Rotation as quaternion (identity)
        glm::vec3 m_Scale = {1.0f, 1.0f,
                             1.0f};  ///< Scale factors for each axis

        mutable glm::mat4 m_CachedModelMatrix =
            glm::mat4(1.0f);  ///< Cached transformation matrix
        mutable bool m_MatrixDirty =
            true;  ///< Flag indicating matrix needs recalculation

    public:
        /**
         * @brief Get the 4x4 transformation matrix for this transform.
         *
         * Calculates or returns a cached 4x4 matrix that represents the
         * complete transformation (translation, rotation, and scale) for use in
         * rendering or physics calculations. The matrix is calculated lazily
         * and cached until the transform properties are modified.
         *
         * @return 4x4 transformation matrix in column-major order
         */
        glm::mat4 GetModelMatrix() const;

        /**
         * @brief Get the inverse of the transformation matrix.
         *
         * Calculates the inverse of the model matrix, which is useful for
         * transforming from world space back to local space or for certain
         * lighting calculations that require the inverse transpose.
         *
         * @return Inverse of the 4x4 transformation matrix
         */
        glm::mat4 GetInverseModelMatrix() const;

        // Property accessors

        /**
         * @brief Get the current world space position.
         *
         * @return 3D position vector
         */
        glm::vec3 GetPosition() const { return m_Position; }

        /**
         * @brief Get the current rotation as Euler angles.
         *
         * @return 3D rotation vector containing pitch, yaw, and roll in degrees
         */
        glm::vec3 GetRotation() const { 
            return glm::degrees(glm::eulerAngles(m_Rotation)); 
        }

        /**
         * @brief Get the current rotation as a quaternion.
         *
         * @return Quaternion representing the current rotation
         */
        glm::quat GetRotationQuat() const { return m_Rotation; }

        /**
         * @brief Get the current scale factors.
         *
         * @return 3D scale vector containing scale factors for each axis
         */
        glm::vec3 GetScale() const { return m_Scale; }

        // Position setters

        /**
         * @brief Set the world space position using a vector.
         *
         * @param position New position in world coordinates
         */
        void SetPosition(glm::vec3 position) {
            m_Position = position;
            m_MatrixDirty = true;
        }

        /**
         * @brief Set the world space position using individual coordinates.
         *
         * @param x X coordinate
         * @param y Y coordinate
         * @param z Z coordinate
         */
        void SetPosition(float x, float y, float z) {
            m_Position = glm::vec3(x, y, z);
            m_MatrixDirty = true;
        }

        // Rotation setters

        /**
         * @brief Set the rotation using Euler angles.
         *
         * @param rotation Euler angles in degrees (pitch, yaw, roll)
         */
        void SetRotation(glm::vec3 rotation) {
            m_Rotation = glm::quat(glm::radians(rotation));
            m_MatrixDirty = true;
        }

        /**
         * @brief Set the rotation using individual Euler angles.
         *
         * @param pitch Rotation around X axis in degrees
         * @param yaw Rotation around Y axis in degrees
         * @param roll Rotation around Z axis in degrees
         */
        void SetRotation(float pitch, float yaw, float roll) {
            m_Rotation = glm::quat(glm::radians(glm::vec3(pitch, yaw, roll)));
            m_MatrixDirty = true;
        }

        /**
         * @brief Set the rotation using a quaternion.
         *
         * @param quaternion Quaternion representing the desired rotation
         */
        void SetRotation(const glm::quat& quaternion) {
            m_Rotation = quaternion;
            m_MatrixDirty = true;
        }

        /**
         * @brief Set rotation to look at a target position.
         *
         * @param target World position to look at
         * @param up Up vector (default: world up)
         */
        void LookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f)) {
            glm::vec3 direction = glm::normalize(target - m_Position);
            m_Rotation = glm::quatLookAt(direction, up);
            m_MatrixDirty = true;
        }

        // Scale setters

        /**
         * @brief Set the scale factors using a vector.
         *
         * @param scale Scale factors for each axis
         */
        void SetScale(glm::vec3 scale) {
            m_Scale = scale;
            m_MatrixDirty = true;
        }

        /**
         * @brief Set the scale factors using individual values.
         *
         * @param x Scale factor for X axis
         * @param y Scale factor for Y axis
         * @param z Scale factor for Z axis
         */
        void SetScale(float x, float y, float z) {
            m_Scale = glm::vec3(x, y, z);
            m_MatrixDirty = true;
        }

        // Relative transformation methods

        /**
         * @brief Apply a relative translation to the current position.
         *
         * Adds the specified delta to the current position, effectively
         * moving the transform by the given amount.
         *
         * @param delta Translation vector to add to current position
         */
        void Translate(const glm::vec3& delta);

        /**
         * @brief Apply a relative rotation to the current rotation.
         *
         * Adds the specified Euler angle deltas to the current rotation.
         *
         * @param eulerDelta Euler angle deltas in degrees to add to current
         * rotation
         */
        void Rotate(const glm::vec3& eulerDelta);

        /**
         * @brief Apply a relative rotation using a quaternion.
         *
         * Multiplies the current rotation by the provided quaternion rotation.
         *
         * @param quaternionDelta Quaternion rotation to apply
         */
        void Rotate(const glm::quat& quaternionDelta) {
            m_Rotation = m_Rotation * quaternionDelta;
            m_MatrixDirty = true;
        }

        /**
         * @brief Rotate around a specific axis by an angle.
         *
         * @param axis Normalized axis vector to rotate around
         * @param angleDegrees Angle to rotate in degrees
         */
        void RotateAroundAxis(const glm::vec3& axis, float angleDegrees) {
            glm::quat deltaRotation = glm::angleAxis(glm::radians(angleDegrees), glm::normalize(axis));
            Rotate(deltaRotation);
        }

        /**
         * @brief Spherically interpolate to a target rotation.
         *
         * @param targetRotation Target quaternion to interpolate towards
         * @param t Interpolation factor (0.0 = current rotation, 1.0 = target rotation)
         */
        void SlerpRotation(const glm::quat& targetRotation, float t) {
            m_Rotation = glm::slerp(m_Rotation, targetRotation, t);
            m_MatrixDirty = true;
        }

        /**
         * @brief Apply a relative scale to the current scale.
         *
         * Multiplies the current scale factors by the provided scale factors.
         *
         * @param scaleFactor Scale factors to multiply with current scale
         */
        void Scale(const glm::vec3& scaleFactor);

        /**
         * @brief Apply a uniform relative scale to all axes.
         *
         * Multiplies all current scale factors by the provided uniform scale
         * factor.
         *
         * @param scaleFactor Uniform scale factor to apply to all axes
         */
        void Scale(float scaleFactor);

        // Directional vector methods

        /**
         * @brief Get the forward direction vector in world space.
         *
         * Calculates the forward direction (negative Z axis in local space)
         * transformed by the current rotation.
         *
         * @return Normalized forward direction vector
         */
        glm::vec3 GetForward() const {
            return m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
        }

        /**
         * @brief Get the right direction vector in world space.
         *
         * Calculates the right direction (positive X axis in local space)
         * transformed by the current rotation.
         *
         * @return Normalized right direction vector
         */
        glm::vec3 GetRight() const {
            return m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f);
        }

        /**
         * @brief Get the up direction vector in world space.
         *
         * Calculates the up direction (positive Y axis in local space)
         * transformed by the current rotation.
         *
         * @return Normalized up direction vector
         */
        glm::vec3 GetUp() const {
            return m_Rotation * glm::vec3(0.0f, 1.0f, 0.0f);
        }
};

}  // namespace Obelisk