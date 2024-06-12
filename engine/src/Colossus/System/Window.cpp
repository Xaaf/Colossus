#include "Colossus/System/Window.h"
#include <utility>
#include "Colossus/Engine.h"
#include "Colossus/Input/Keyboard.h"

using namespace Colossus;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    LOG_TRACE("Window", "Resizing to " << width << "x" << height);
    glViewport(0, 0, width, height);
}

Window::Window(std::string window_name, int width, int height) {
    this->m_WindowName = std::move(window_name);
    this->m_Width = width;
    this->m_Height = height;

    if (!glfwInit()) {
        // @TODO: Throw an error instead
        LOG_ERROR("Window", "Failed to initialise GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::create() {
    m_Window =
        glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), NULL, NULL);

    if (m_Window == nullptr) {
        LOG_ERROR("Window", "Failed to create window!");

        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

    Keyboard* keyboard = Keyboard::getInstance();
    glfwSetKeyCallback(m_Window, (GLFWkeyfun)&Keyboard::callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Window", "Failed to initialise GLAD!");
    }

    glViewport(0, 0, m_Width, m_Height);
}

void Window::tick() {
    glfwSwapBuffers(m_Window);

    if (glfwWindowShouldClose(m_Window)) {
        Engine::getInstance()->stop();
    }
}

void Window::close() { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }
