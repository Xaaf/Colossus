#include "Obelisk/Renderer/Window.h"
#include "Obelisk/Core/Camera.h"
#include "Obelisk/Input/Keyboard.h"
#include "Obelisk/Input/Mouse.h"
#include "Obelisk/Scene/Entity.h"
#include "Obelisk/Scene/Scene.h"
#include "stb_image.h"

namespace Obelisk {
Window::~Window() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
}

int Window::Create(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
        return -1;
    }

    // Set error callback for better debugging
    glfwSetErrorCallback([](int error, const char* description) {
        LOG_ERROR("GLFW Error {}: {}", error, description);
    });

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
    glfwSetFramebufferSizeCallback(
        m_Window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });

    // Set input callbacks
    glfwSetKeyCallback(m_Window,
                       [](GLFWwindow* window, int key, int scancode, int action,
                          int mods) { Keyboard::RegisterAction(key, action); });

    glfwSetMouseButtonCallback(
        m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            Mouse::RegisterAction(button, action);
        });

    glfwSetCursorPosCallback(m_Window,
                             [](GLFWwindow* window, double xpos, double ypos) {
                                 Mouse::RegisterMove(xpos, ypos);
                             });

    glEnable(GL_DEPTH_TEST);

    LOG_INFO("Initialised OpenGL viewport ({}x{})", width, height);
    LOG_INFO("> GLFW v{}, OpenGL v{}", glfwGetVersionString(),
             reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    LOG_INFO("> Graphics Card: {}, {}",
             reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
             reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    return 1;
}

void Window::Tick() {
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_Scene) {
        Camera* camera = m_Scene->GetCamera();
        if (camera) {
            // Use camera-based rendering for proper 3D pipeline
            for (auto entity : m_Scene->GetEntities()) {
                entity->Draw(*camera);
            }
        } else {
            // Fallback to legacy rendering if no camera is set
            LOG_WARN("No camera set for scene, using legacy rendering");
            for (auto entity : m_Scene->GetEntities()) {
                entity->Draw();
            }
        }
    } else {
        LOG_WARN("No active scene!");
    }

    glUseProgram(0);

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_Window); }

}  // namespace Obelisk