#include "Obelisk/ObeliskAPI.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"
#include "Obelisk/Renderer/Texture.h"
#include "Obelisk/Scene/Entity.h"

Obelisk::Mesh mesh;
Obelisk::Shader shader;
Obelisk::Texture texture;
Obelisk::Entity entity;
Obelisk::Scene scene;

glm::mat4 trans = glm::mat4(1.0f);

void MyInit() {
    trans =
        glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

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

    mesh = Obelisk::Mesh(meshVertices, meshIndices);
    shader = Obelisk::Shader("shaders/basic.vert", "shaders/basic.frag");
    texture = Obelisk::Texture("textures/Testing.jpg");

    auto meshPtr = std::make_shared<Obelisk::Mesh>(mesh);
    auto shaderPtr = std::make_shared<Obelisk::Shader>(shader);
    auto texturePtr = std::make_shared<Obelisk::Texture>(texture);

    entity = Obelisk::Entity(meshPtr, shaderPtr, texturePtr);
    scene.AddEntity(&entity);

    entity.GetShader()->SetMat4("transform", trans);

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