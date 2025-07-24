#include "Obelisk/ObeliskAPI.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"
#include "Obelisk/Renderer/Texture.h"
#include "Obelisk/Scene/Entity.h"

Obelisk::Entity entity;
Obelisk::Scene scene;

void MyInit() {
    std::vector<Obelisk::Vertex> meshVertices = {
        // Bottom Left
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        // Bottom Right
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        // Top Right
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, 0.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        // Top Left
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, 0.0f),
                        glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))};

    std::vector<unsigned int> meshIndices = {// First triangle
                                             0, 1, 2,
                                             // Second Triangle
                                             2, 3, 0};

    entity = Obelisk::Entity(
        std::make_shared<Obelisk::Mesh>(meshVertices, meshIndices),
        std::make_shared<Obelisk::Shader>("basic.vert", "basic.frag"),
        std::make_shared<Obelisk::Texture>("Testing.jpg"));
    scene.AddEntity(&entity);

    // Quaternion rotation test - rotate by 45 degrees around Z axis
    entity.GetTransform().SetPosition(0.0f, 0.0f, 0.0f);
    entity.GetTransform().SetRotation(0.0f, 0.0f,
                                      45.0f);  // 45° rotation around Z axis
    entity.GetTransform().SetScale(1.0f, 1.0f, 1.0f);

    // Log the rotation for verification using new format-based logging
    glm::vec3 euler = entity.GetTransform().GetRotation();
    glm::quat quat = entity.GetTransform().GetRotationQuat();

    LOG_INFO("Applied 45 degree Z rotation to mesh using quaternions");
    LOG_INFO("Euler angles: ({:.2f}, {:.2f}, {:.2f})", euler.x, euler.y,
             euler.z);
    LOG_INFO("Quaternion: w={:.3f} x={:.3f} y={:.3f} z={:.3f}", quat.w, quat.x,
             quat.y, quat.z);
    LOG_INFO("Mesh should appear rotated by 45 degrees");

    Obelisk::ObeliskAPI::Get().GetWindow()->SetScene(&scene);
}

void MyUpdate() {}

int main() {
    Obelisk::ObeliskAPI::Get().SetUpdateCallback(MyUpdate);
    Obelisk::ObeliskAPI::Get().SetInitCallback(MyInit);

    Obelisk::ObeliskAPI::Get().Init();
    Obelisk::ObeliskAPI::Get().Run();
    Obelisk::ObeliskAPI::Get().Shutdown();

    return 0;
}