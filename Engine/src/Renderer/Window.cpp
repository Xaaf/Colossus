#include "Obelisk/Renderer/Window.h"

#include "GLFW/glfw3.h"
#include "Obelisk/Renderer/Mesh.h"

namespace Obelisk {
Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }

    glfwTerminate();
}

// --------- TEMPORARY TESTING ---------
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
unsigned int vertexShader;

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
unsigned int fragmentShader;

unsigned int shaderProgram;

unsigned int VAO, VBO, EBO;

Mesh triangleMesh;
// -------------------------------------

int Window::Create(int width, int height, const char* title) {
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

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
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

    // Vertex Shader creation
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n> " << infoLog);
    }

    // Fragment shader creation
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n> " << infoLog);
    }

    // Shader program creation
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n> " << infoLog);
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // -------------------------------------
    return 1;
}

void Window::Tick() {
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    triangleMesh.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    triangleMesh.Unbind();

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}
}