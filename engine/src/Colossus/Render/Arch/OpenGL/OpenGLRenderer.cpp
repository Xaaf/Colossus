#include "Colossus/Render/Arch/OpenGL/OpenGLRenderer.h"
#include "Colossus/Engine.h"
#include "Colossus/Input/Keyboard.h"
#include "Colossus/Render/Arch/OpenGL/Shader.h"
#include "Colossus/Render/Arch/OpenGL/Texture.h"

using namespace Colossus;

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

unsigned int inds[] = {0, 1, 3, 1, 2, 3};

unsigned int VBO, VAO, EBO = 0;
Shader shader;
Texture texture;

void temp_shaders() {
    shader.create("assets/shaders/default.vert", "assets/shaders/default.frag");
    texture.create("assets/textures/wall.jpg");

    //==== Prepare For Rendering (VAO, VBO, EBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)nullptr);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    LOG_INFO("OpenGL", "All done!");
}

// =======================

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    LOG_TRACE("OpenGL", "Resizing to " << width << "x" << height);
    glViewport(0, 0, width, height);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action,
                       int mods) {
    LOG_TRACE("OpenGL", "Passing key callback through abstraction layer");
    Keyboard::callback(key, action);
}

bool OpenGLRenderer::initialise() {
    LOG_TRACE("OpenGL", "Calling OpenGLRenderer::initialise");

    // Initialise
    if (!glfwInit()) {
        LOG_ERROR("OpenGL", "Failed to initialise GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool OpenGLRenderer::createWindow() {
    LOG_TRACE("OpenGL", "Calling OpenGLRenderer::createWindow");

    m_WindowName = "Heroes of Colossus";
    m_Width = 1280;
    m_Height = 720;

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(),
                                nullptr, nullptr);

    if (m_Window == nullptr) {
        LOG_ERROR("OpenGL", "Failed to createWindow window!");
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Window, keyboard_callback);

    LOG_INFO("OpenGL", "Successfully set callbacks");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("OpenGL", "Failed to initialise GLAD!");
        glfwTerminate();

        return false;
    }

    glViewport(0, 0, m_Width, m_Height);

    LOG_INFO("OpenGL",
             "Initialised OpenGL viewport with " << m_Width << "x" << m_Height);
    LOG_INFO("OpenGL", " > GLFW v" << glfwGetVersionString() << ", OpenGL v"
                                   << glGetString(GL_VERSION));
    LOG_INFO("OpenGL", " > Graphics Card: " << glGetString(GL_RENDERER) << ", "
                                            << glGetString(GL_VENDOR));

    temp_shaders();

    return true;
}

void OpenGLRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glBindTexture(GL_TEXTURE_2D, texture.getId());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

    if (glfwWindowShouldClose(m_Window)) {
        Engine::getInstance()->stop();
    }
}
void OpenGLRenderer::stop() {
    LOG_INFO("OpenGL", "Terminating GLFW");
    glfwTerminate();
}
