#include "Obelisk/ObeliskAPI.h"

#include "Obelisk/Renderer/Mesh.h"

namespace Obelisk {
ObeliskAPI* ObeliskAPI::s_Instance = nullptr;

ObeliskAPI& ObeliskAPI::Get() {
    if (!s_Instance)
        s_Instance = new ObeliskAPI();

    return *s_Instance;
}

void ObeliskAPI::Init(int width, int height, const char* title) {
    LOG_INFO("Initializing Obelisk Engine...");
    m_Window = new Window();
    if (!m_Window->Create(1280, 720, "Heroes of Colossus")) {
        LOG_ERROR("Failed to create window!");
    }

    LOG_INFO("Finished initializing Obelisk Engine!");
}

void ObeliskAPI::Run() {
    LOG_INFO("Running Obelisk Engine...");

    // --------- TEMPORARY TESTING ---------
    std::vector<Vertex> triangleVertices = {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
               glm::vec2(0.0f, 0.0f)), // Bottom-left (Red)
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec2(1.0f, 0.0f)), // Bottom-right (Green)
        Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
               glm::vec2(0.5f, 1.0f)) // Top-center (Blue)
    };

    std::vector<GLuint> triangleIndices = {
        0, 1, 2
    };

    Mesh triangleMesh(triangleVertices, triangleIndices);
    // -------------------------------------

    while (!m_Window->ShouldClose()) {
        m_Window->Tick();

        triangleMesh.Bind();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        triangleMesh.Unbind();
    }
}

void ObeliskAPI::Shutdown() {
    LOG_INFO("Shutting down Obelisk Engine...");
    delete m_Window;
}
}