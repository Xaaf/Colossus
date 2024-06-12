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

void Engine::initialise(const std::string& window_name, const std::string& renderer) {
    LOG_INFO("Engine", "Initialising with name '" << window_name << "'");

    m_Window = new Window(window_name, 1280, 720, RendererFactory::stringToRenderType(renderer));
    m_Window->create();

    m_IsRunning = true;
}

void Engine::step() {
    m_Window->update();
//    renderer->render();
}

void Engine::stop() { m_IsRunning = false; }

bool Engine::isRunning() const { return m_IsRunning; }
