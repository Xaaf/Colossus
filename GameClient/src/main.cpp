#include "Obelisk/Core/Camera.h"
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

    // Log the rotation for verification using new format-based logging
    glm::vec3 euler = entity.GetTransform().GetRotation();
    glm::quat quat = entity.GetTransform().GetRotationQuat();

    LOG_INFO("Created a 3D textured cube for better camera demonstration");
    LOG_INFO("Cube initial rotation - Euler angles: ({:.2f}, {:.2f}, {:.2f})",
             euler.x, euler.y, euler.z);
    LOG_INFO("Quaternion: w={:.3f} x={:.3f} y={:.3f} z={:.3f}", quat.w, quat.x,
             quat.y, quat.z);
    LOG_INFO("Mesh should appear rotated by 45 degrees");

    // Camera setup and demonstration
    camera.SetPosition(
        glm::vec3(0.0f, 0.0f, 3.0f));        // Position camera 3 units back
    camera.SetFieldOfView(60.0f);            // Set a nice field of view
    camera.SetAspectRatio(16.0f / 9.0f);     // Standard widescreen aspect ratio
    camera.SetClippingPlanes(0.1f, 100.0f);  // Set appropriate clipping planes
    camera.SetProjectionType(
        Obelisk::Camera::ProjectionType::Perspective);  // Use perspective
                                                        // projection

    // Demonstrate camera controls
    LOG_INFO("=== Camera System Demo ===");
    LOG_INFO("Camera position: ({:.2f}, {:.2f}, {:.2f})",
             camera.GetPosition().x, camera.GetPosition().y,
             camera.GetPosition().z);
    LOG_INFO("Camera FOV: {:.1f} degrees", camera.GetFieldOfView());
    LOG_INFO("Camera aspect ratio: {:.2f}", camera.GetAspectRatio());

    // Test camera rotation
    camera.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));  // Reset rotation
    LOG_INFO("Camera forward direction: ({:.2f}, {:.2f}, {:.2f})",
             camera.GetForward().x, camera.GetForward().y,
             camera.GetForward().z);
    LOG_INFO("Camera right direction: ({:.2f}, {:.2f}, {:.2f})",
             camera.GetRight().x, camera.GetRight().y, camera.GetRight().z);
    LOG_INFO("Camera up direction: ({:.2f}, {:.2f}, {:.2f})", camera.GetUp().x,
             camera.GetUp().y, camera.GetUp().z);

    // Test LookAt functionality
    camera.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));  // Look at the mesh
    LOG_INFO("After LookAt(0,0,0) - Camera forward: ({:.2f}, {:.2f}, {:.2f})",
             camera.GetForward().x, camera.GetForward().y,
             camera.GetForward().z);

    // Test projection switching
    LOG_INFO("Current projection: {}",
             camera.GetProjectionType() ==
                     Obelisk::Camera::ProjectionType::Perspective
                 ? "Perspective"
                 : "Orthographic");

    // Demonstrate matrix access
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    glm::mat4 projMatrix = camera.GetProjectionMatrix();
    glm::mat4 viewProjMatrix = camera.GetViewProjectionMatrix();

    LOG_INFO("View matrix calculated successfully");
    LOG_INFO("Projection matrix calculated successfully");
    LOG_INFO("View-Projection matrix calculated successfully");

    // Test screen-to-world ray conversion
    glm::vec3 centerRay =
        camera.ScreenToWorldRay(glm::vec2(0.0f, 0.0f));  // Center of screen
    LOG_INFO("Center screen ray direction: ({:.2f}, {:.2f}, {:.2f})",
             centerRay.x, centerRay.y, centerRay.z);

    Obelisk::ObeliskAPI::Get().GetWindow()->SetScene(&scene);

    // Set the camera for the scene to enable proper 3D rendering
    scene.SetCamera(&camera);
}

float timestep = 0.00016f;

void MyUpdate() {
    // Simple camera orbit demonstration (using frame-based timing for now)
    static float time = 0.0f;
    time += timestep;  // Temporary fixed timestep until we add Time class

    // Orbit the camera around the cube
    float radius = 4.0f;  // Increased radius for better view of the cube
    float x = radius * cos(time * 0.3f);  // Slower orbit for better observation
    float z = radius * sin(time * 0.3f);
    float y = sin(time * 0.2f) * 1.0f;  // Add some vertical movement

    camera.SetPosition(glm::vec3(x, y, z));
    camera.LookAt(glm::vec3(0.0f, 0.0f, 0.0f));  // Always look at the cube

    // Slowly rotate the cube to show different faces
    float rotationSpeed = 15.0f;  // degrees per second (approximate)
    static float cubeRotation = 0.0f;
    cubeRotation += rotationSpeed * timestep;  // Temporary fixed timestep
    entity.GetTransform().SetRotation(cubeRotation * 0.7f, cubeRotation,
                                      cubeRotation * 0.5f);
}

int main() {
    Obelisk::ObeliskAPI::Get().SetUpdateCallback(MyUpdate);
    Obelisk::ObeliskAPI::Get().SetInitCallback(MyInit);

    Obelisk::ObeliskAPI::Get().Init();
    Obelisk::ObeliskAPI::Get().Run();
    Obelisk::ObeliskAPI::Get().Shutdown();

    return 0;
}