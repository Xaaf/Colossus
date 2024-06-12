#include "colossus/Engine.h"
#include "colossus/input/Keyboard.h"

using namespace Colossus;

Engine* Engine::instance = nullptr;

Engine::Engine() { m_IsRunning = false; }
Engine::~Engine() { delete m_Window; }

Engine* Engine::getInstance() {
    if (instance == nullptr) {
        instance = new Engine();
    }

    return instance;
}

void Engine::initialise(const std::string& window_name) {
    LOG_INFO("Engine", "Initialising with name '" << window_name << "'");

    if (m_Window) {
        LOG_WARN("Engine", "A window already exists, overwriting it...");

        delete m_Window;
    }

    m_Window = new Window(window_name, 1280, 720);
    m_Window->create();
    m_IsRunning = true;
}

void Engine::mainLoop() {
    while (m_IsRunning) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Window->tick();
        glfwPollEvents();

        if (Keyboard::isKeyPressed(GLFW_KEY_ESCAPE)) {
            stop();
        }
    }
}

void Engine::stop() { m_IsRunning = false; }