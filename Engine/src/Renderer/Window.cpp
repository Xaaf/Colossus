#include "Obelisk/Renderer/Window.h"

#include "GLFW/glfw3.h"
#include "Obelisk/Renderer/Mesh.h"
#include "Obelisk/Renderer/Shader.h"

namespace Obelisk {
Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }

    glfwTerminate();
}

// --------- TEMPORARY TESTING ---------
Mesh triangleMesh;
Shader shader;
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
    std::vector<Vertex> triangleVertices = {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f)), // Bottom-left (Red)
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f)),  // Bottom-right (Green)
        Vertex(glm::vec3(0.0f, 0.5f, 0.0f))    // Top-center (Blue)
    };

    std::vector<unsigned int> triangleIndices = {
        0, 1, 2
    };

    triangleMesh = Mesh(triangleVertices, triangleIndices);
    shader = Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    return 1;
}

void Window::Tick() {
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float timeValue = glfwGetTime();
    float blueValue = (sin(timeValue) / 2.0f) + 0.5f;

    shader.Use();
    shader.SetVec4("someColor", glm::vec4(0.0f, 0.0f, blueValue, 1.0f));

    triangleMesh.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    triangleMesh.Unbind();

    glUseProgram(0);

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}
}