#include "Obelisk/Renderer/Window.h"

#include "stb_image.h"
#include "GLFW/glfw3.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"
#include "Obelisk/Renderer/Texture.h"

namespace Obelisk {
Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }

    glfwTerminate();
}

// --------- TEMPORARY TESTING ---------
Mesh mesh;
Shader shader;
Texture texture;
// -------------------------------------

int Window::Create(int width, int height, std::string title) {
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(m_Window,
                                   [](GLFWwindow* window, int width,
                                      int height) {
                                       glViewport(0, 0, width, height);
                                   });

    glEnable(GL_DEPTH_TEST);

    LOG_INFO("Initialised OpenGL viewport (" << width << "x" << height
        << ")");
    LOG_INFO("> GLFW v" << glfwGetVersionString() << ", OpenGL v"
        << glGetString(GL_VERSION));
    LOG_INFO("> Graphics Card: " << glGetString(GL_RENDERER) << ", "
        << glGetString(GL_VENDOR));

    // --------- TEMPORARY TESTING ---------
    std::vector<Vertex> meshVertices = {
        // Bottom Left
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
               glm::vec2(0.0f, 0.0f)),
        // Bottom Right
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec2(1.0f, 0.0f)),
        // Top Right
        Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
               glm::vec2(1.0f, 1.0f)),
        // Top Left
        Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
               glm::vec2(0.0f, 1.0f))
    };

    std::vector<unsigned int> meshIndices = {
        // First triangle
        0, 1, 2,
        // Second Triangle
        2, 3, 0
    };

    mesh = Mesh(meshVertices, meshIndices);
    shader = Shader("shaders/basic.vert", "shaders/basic.frag");
    texture = Texture("textures/Testing.jpg");
    // -------------------------------------

    return 1;
}

void Window::Tick() {
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture.Bind();
    shader.Use();

    mesh.Bind();
    glDrawElements(GL_TRIANGLES, mesh.GetNumberOfIndices(), GL_UNSIGNED_INT,
                   nullptr);
    Obelisk::Mesh::Unbind();

    glUseProgram(0);

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}
}