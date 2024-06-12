#include "Colossus/Render/Renderers/OpenGLRenderer.h"
#include "Colossus/Engine.h"

using namespace Colossus;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    LOG_TRACE("Window", "Resizing to " << width << "x" << height);
    glViewport(0, 0, width, height);
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

bool OpenGLRenderer::create() {
    LOG_TRACE("OpenGL", "Calling OpenGLRenderer::create");

    m_WindowName = "Heroes of Colossus";
    m_Width = 1280;
    m_Height = 720;

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(),
                                nullptr, nullptr);

    if (m_Window == nullptr) {
        LOG_ERROR("OpenGL", "Failed to create window!");
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    LOG_INFO("OpenGL", "Successfully set callbacks.");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("OpenGL", "Failed to initialise GLAD!");
        glfwTerminate();

        return false;
    }

    glViewport(0, 0, m_Width, m_Height);
    LOG_INFO("OpenGL",
             "Initialised OpenGL viewport with " << m_Width << "x" << m_Height);

    return true;
}

void OpenGLRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
