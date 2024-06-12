#include "Colossus/Engine.h"
#include "Colossus/Input/Keyboard.h"

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

void Engine::initialise(const std::string& window_name, RendererType type) {
    LOG_INFO("Engine", "Initialising with name '" << window_name << "'");

    renderer = RendererFactory::createRenderer(type);

    if (!renderer->initialise()) {
        LOG_ERROR("Engine", "Could not initialise renderer!");
    }

    if (m_Window) {
        LOG_WARN("Engine", "A window already exists, overwriting it...");

        delete m_Window;
    }

    m_Window = new Window(window_name, 1280, 720);
    m_Window->create();
    m_IsRunning = true;
}

void Engine::step() {
    m_Window->tick();
    renderer->render();
}

void Engine::stop() { m_IsRunning = false; }

bool Engine::isRunning() const { return m_IsRunning; }
