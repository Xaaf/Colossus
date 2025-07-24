#include "Obelisk/Core/Camera.h"
#include "Obelisk/Logging/Log.h"

namespace Obelisk {

Camera::Camera() {
    UpdateProjectionMatrix();
    UpdateViewMatrix();
    LOG_TRACE("Camera created with default settings (FOV: {}, Aspect: {:.2f})",
              m_FOV, m_AspectRatio);
}

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearPlane(nearPlane),
      m_FarPlane(farPlane) {
    UpdateProjectionMatrix();
    UpdateViewMatrix();
    LOG_TRACE(
        "Camera created with custom settings (FOV: {}, Aspect: {:.2f}, Near: "
        "{}, Far: {})",
        m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
}

// === Position Controls ===

void Camera::SetPosition(const glm::vec3& position) {
    m_Transform.SetPosition(position);
    MarkViewDirty();
}

void Camera::Move(const glm::vec3& offset) {
    m_Transform.SetPosition(m_Transform.GetPosition() + offset);
    MarkViewDirty();
}

// === Rotation Controls ===

void Camera::SetRotation(const glm::vec3& rotation) {
    m_Transform.SetRotation(rotation);
    MarkViewDirty();
}

void Camera::SetRotation(const glm::quat& rotation) {
    m_Transform.SetRotation(rotation);
    MarkViewDirty();
}

void Camera::Rotate(const glm::vec3& rotation) {
    glm::vec3 currentRotation = m_Transform.GetRotation();
    m_Transform.SetRotation(currentRotation + rotation);
    MarkViewDirty();
}

void Camera::LookAt(const glm::vec3& target, const glm::vec3& up) {
    m_Transform.LookAt(target, up);
    MarkViewDirty();
}

// === Projection Settings ===

void Camera::SetProjectionType(ProjectionType type) {
    if (m_ProjectionType != type) {
        m_ProjectionType = type;
        MarkProjectionDirty();
        LOG_TRACE("Camera projection type changed to {}",
                  type == ProjectionType::Perspective ? "Perspective"
                                                      : "Orthographic");
    }
}

void Camera::SetFieldOfView(float fov) {
    if (m_FOV != fov) {
        m_FOV = fov;
        MarkProjectionDirty();
        LOG_TRACE("Camera FOV changed to {}", m_FOV);
    }
}

void Camera::SetAspectRatio(float aspectRatio) {
    if (m_AspectRatio != aspectRatio) {
        m_AspectRatio = aspectRatio;
        MarkProjectionDirty();
        LOG_TRACE("Camera aspect ratio changed to {:.2f}", m_AspectRatio);
    }
}

void Camera::SetClippingPlanes(float nearPlane, float farPlane) {
    if (m_NearPlane != nearPlane || m_FarPlane != farPlane) {
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;
        MarkProjectionDirty();
        LOG_TRACE("Camera clipping planes changed (Near: {}, Far: {})",
                  m_NearPlane, m_FarPlane);
    }
}

void Camera::SetOrthographicSize(float size) {
    if (m_OrthographicSize != size) {
        m_OrthographicSize = size;
        if (m_ProjectionType == ProjectionType::Orthographic) {
            MarkProjectionDirty();
            LOG_TRACE("Camera orthographic size changed to {}",
                      m_OrthographicSize);
        }
    }
}

// === Matrix Access ===

const glm::mat4& Camera::GetViewMatrix() const {
    UpdateViewMatrix();
    return m_ViewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const {
    UpdateProjectionMatrix();
    return m_ProjectionMatrix;
}

glm::mat4 Camera::GetViewProjectionMatrix() const {
    return GetProjectionMatrix() * GetViewMatrix();
}

// === Utility Methods ===

glm::vec3 Camera::ScreenToWorldRay(const glm::vec2& screenPos) const {
    // Convert from normalized device coordinates to clip space
    glm::vec4 clipCoords = glm::vec4(screenPos.x, screenPos.y, -1.0f, 1.0f);

    // Convert to eye space
    glm::mat4 invProjection = glm::inverse(GetProjectionMatrix());
    glm::vec4 eyeCoords = invProjection * clipCoords;
    eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

    // Convert to world space
    glm::mat4 invView = glm::inverse(GetViewMatrix());
    glm::vec3 worldRay = glm::vec3(invView * eyeCoords);

    return glm::normalize(worldRay);
}

glm::vec2 Camera::WorldToScreen(const glm::vec3& worldPos) const {
    glm::mat4 viewProjection = GetViewProjectionMatrix();
    glm::vec4 clipSpace = viewProjection * glm::vec4(worldPos, 1.0f);

    // Perspective divide
    if (clipSpace.w != 0.0f) {
        clipSpace /= clipSpace.w;
    }

    // Convert to normalized device coordinates
    return glm::vec2(clipSpace.x, clipSpace.y);
}

// === Private Methods ===

void Camera::UpdateProjectionMatrix() const {
    if (!m_ProjectionDirty) return;

    if (m_ProjectionType == ProjectionType::Perspective) {
        m_ProjectionMatrix = glm::perspective(
            glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
    } else {
        float halfWidth = m_OrthographicSize * m_AspectRatio;
        float halfHeight = m_OrthographicSize;
        m_ProjectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight,
                                        halfHeight, m_NearPlane, m_FarPlane);
    }

    m_ProjectionDirty = false;
}

void Camera::UpdateViewMatrix() const {
    if (!m_ViewDirty) return;

    // Calculate view matrix from transform
    glm::vec3 position = m_Transform.GetPosition();
    glm::vec3 forward = m_Transform.GetForward();
    glm::vec3 up = m_Transform.GetUp();

    m_ViewMatrix = glm::lookAt(position, position + forward, up);
    m_ViewDirty = false;
}

}  // namespace Obelisk