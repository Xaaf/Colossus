#include "Colossus/Render/Window.h"

using namespace Colossus;

Window::Window(std::string window_name, int width, int height,
               RendererType rendererType) {
    LOG_TRACE("Window", "Calling Window::Window");
    Renderer::getInstance();
    Renderer::createRenderer(rendererType);
}

Window::~Window() { LOG_TRACE("Window", "Calling Window::~Window"); }

void Window::create() {
    LOG_TRACE("Window", "Calling Window::createWindow");

    if (!Renderer::getRenderer()->createWindow()) {
        LOG_ERROR("Window", "Failed to create new window!");
    }
}

void Window::update() { Renderer::getRenderer()->render(); }

void Window::close() {
    LOG_TRACE("Window", "Calling Window::close");
    Renderer::getRenderer()->stop();
}
