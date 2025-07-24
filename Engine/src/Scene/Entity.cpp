#include "Obelisk/Scene/Entity.h"
#include "Obelisk/Core/Camera.h"

namespace Obelisk {
Entity::Entity() {
    m_Mesh = nullptr;
    m_Shader = nullptr;
    m_Texture = nullptr;
}

Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader,
               std::shared_ptr<Texture> texture) {
    m_Mesh = mesh;
    m_Shader = shader;
    m_Texture = texture;
}

void Entity::SetMesh(std::shared_ptr<Mesh> mesh) { m_Mesh = mesh; }

void Entity::SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }

void Entity::SetTexture(std::shared_ptr<Texture> texture) {
    m_Texture = texture;
}

std::shared_ptr<Mesh> Entity::GetMesh() const { return m_Mesh; }

std::shared_ptr<Shader> Entity::GetShader() const { return m_Shader; }

std::shared_ptr<Texture> Entity::GetTexture() const { return m_Texture; }

void Entity::Draw(const Camera& camera) const {
    if (!m_Mesh) {
        LOG_ERROR("No mesh attached to entity!");
        return;
    }

    if (!m_Shader) {
        LOG_ERROR("Can't draw Mesh without Shader!");
        return;
    }

    m_Shader->Use();

    // Set the model-view-projection matrices
    glm::mat4 modelMatrix = m_Transform.GetModelMatrix();
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
    
    m_Shader->SetMat4("model", modelMatrix);
    m_Shader->SetMat4("view", viewMatrix);
    m_Shader->SetMat4("projection", projectionMatrix);

    if (m_Texture) {
        m_Texture->Bind();
    }

    m_Mesh->Bind();
    glDrawElements(GL_TRIANGLES, m_Mesh->GetNumberOfIndices(), GL_UNSIGNED_INT,
                   nullptr);
    m_Mesh->Unbind();
}

void Entity::Draw() const {
    if (!m_Mesh) {
        LOG_ERROR("No mesh attached to entity!");
        return;
    }

    if (!m_Shader) {
        LOG_ERROR("Can't draw Mesh without Shader!");
        return;
    }

    m_Shader->Use();

    // Legacy method - uses combined transform matrix
    glm::mat4 modelMatrix = m_Transform.GetModelMatrix();
    m_Shader->SetMat4("transform", modelMatrix);

    if (m_Texture) {
        m_Texture->Bind();
    }

    m_Mesh->Bind();
    glDrawElements(GL_TRIANGLES, m_Mesh->GetNumberOfIndices(), GL_UNSIGNED_INT,
                   nullptr);
    m_Mesh->Unbind();
}
}  // namespace Obelisk