#include "Colossus/Render/Window.h"

using namespace Colossus;

Window::Window(std::string window_name, int width, int height,
               RendererType rendererType) {
    LOG_TRACE("Window", "Calling Window::Window");

    m_Renderer = RendererFactory::createRenderer(rendererType);
    if (!m_Renderer->initialise()) {
        LOG_ERROR("Window", "Failed to initialise rendererType!");
    }
}

Window::~Window() { LOG_TRACE("Window", "Calling Window::~Window"); }

void Window::create() {
    LOG_TRACE("Window", "Calling Window::create");

    if (!m_Renderer->create()) {
        LOG_ERROR("Window", "Failed to create new window!");
    }
}

void Window::update() {
    m_Renderer->render();
}

void Window::close() { LOG_TRACE("Window", "Calling Window::close"); }