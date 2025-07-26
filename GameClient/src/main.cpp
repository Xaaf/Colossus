#include "Obelisk/Core/Camera.h"
#include "Obelisk/Core/Time.h"
#include "Obelisk/Input/InputCodes.h"
#include "Obelisk/Input/Keyboard.h"
#include "Obelisk/ObeliskAPI.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"
#include "Obelisk/Renderer/Texture.h"
#include "Obelisk/Scene/Entity.h"

Obelisk::Entity entity;
Obelisk::Scene scene;
Obelisk::Camera camera;

void MyInit() {
    // Create a 3D cube instead of a flat quad
    std::vector<Obelisk::Vertex> meshVertices = {
        // Front face
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),
                        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, 0.5f),
                        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, 0.5f),
                        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),
                        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),

        // Back face
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),
                        glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),
                        glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, -0.5f),
                        glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, -0.5f),
                        glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)),

        // Left face
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),
                        glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),
                        glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),
                        glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),
                        glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)),

        // Right face
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, 0.5f),
                        glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, 0.5f),
                        glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, -0.5f),
                        glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, -0.5f),
                        glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),

        // Bottom face
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),
                        glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, -0.5f),
                        glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, -0.5f, 0.5f),
                        glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),
                        glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),

        // Top face
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),
                        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
        Obelisk::Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),
                        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, 0.5f),
                        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        Obelisk::Vertex(glm::vec3(0.5f, 0.5f, -0.5f),
                        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f))};

    std::vector<unsigned int> meshIndices = {// Front face
                                             0, 1, 2, 2, 3, 0,
                                             // Back face
                                             4, 5, 6, 6, 7, 4,
                                             // Left face
                                             8, 9, 10, 10, 11, 8,
                                             // Right face
                                             12, 13, 14, 14, 15, 12,
                                             // Bottom face
                                             16, 17, 18, 18, 19, 16,
                                             // Top face
                                             20, 21, 22, 22, 23, 20};

    entity = Obelisk::Entity(
        std::make_shared<Obelisk::Mesh>(meshVertices, meshIndices),
        std::make_shared<Obelisk::Shader>("basic.vert", "basic.frag"),
        std::make_shared<Obelisk::Texture>("Testing.jpg"));
    scene.AddEntity(&entity);

    // Position the cube at the origin and give it a slight initial rotation
    entity.GetTransform().SetPosition(0.0f, 0.0f, 0.0f);
    entity.GetTransform().SetRotation(
        15.0f, 25.0f, 0.0f);  // Slight initial rotation to show 3D structure
    entity.GetTransform().SetScale(1.0f, 1.0f, 1.0f);

    // Camera setup and demonstration
    camera.SetPosition(
        glm::vec3(0.0f, 0.0f, 3.0f));        // Position camera 3 units back
    camera.SetFieldOfView(60.0f);            // Set a nice field of view
    camera.SetAspectRatio(16.0f / 9.0f);     // Standard widescreen aspect ratio
    camera.SetClippingPlanes(0.1f, 100.0f);  // Set appropriate clipping planes
    camera.SetProjectionType(
        Obelisk::Camera::ProjectionType::Perspective);  // Use perspective
                                                        // projection

    camera.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));  // Reset rotation

    // Set the window's scene and camera for proper 3D rendering
    Obelisk::ObeliskAPI::Get().GetWindow()->SetScene(&scene);
    scene.SetCamera(&camera);
}

void MyUpdate() {
    // Simple camera orbit demonstration using proper delta time
    static float time = 0.0f;
    time += Obelisk::Time::GetDeltaTime();  // Frame-independent timing

    // Orbit the camera around the cube
    float radius = 4.0f;      // Increased radius for better view of the cube
    float orbitSpeed = 0.3f;  // Radians per second
    float x = radius * cos(time * orbitSpeed);
    float z = radius * sin(time * orbitSpeed);
    float y = sin(time * 0.2f) * 1.0f;  // Add some vertical movement

    camera.SetPosition(glm::vec3(x, y, z));
    camera.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));  // Always look at the cube

    // Slowly rotate the cube to show different faces
    float rotationSpeed = 15.0f;  // degrees per second
    static float cubeRotation = 0.0f;
    cubeRotation += rotationSpeed * Obelisk::Time::GetDeltaTime();
    entity.GetTransform().SetRotation(cubeRotation * 0.7f, cubeRotation,
                                      cubeRotation * 0.5f);

    // Log frame rate occasionally for performance monitoring
    static float lastFPSLogTime = 0.0f;
    if (Obelisk::Time::HasIntervalPassed(2.0f, lastFPSLogTime)) {
        LOG_INFO("Performance: {:.1f} FPS, {:.2f}ms frame time, {:.1f} avg FPS",
                 Obelisk::Time::GetFPS(), Obelisk::Time::GetFrameTimeMS(),
                 Obelisk::Time::GetAverageFPS());
    }
}

int main() {
    Obelisk::ObeliskAPI::Get().SetUpdateCallback(MyUpdate);
    Obelisk::ObeliskAPI::Get().SetInitCallback(MyInit);

    Obelisk::ObeliskAPI::Get().Init();
    Obelisk::ObeliskAPI::Get().Run();
    Obelisk::ObeliskAPI::Get().Shutdown();

    return 0;
}