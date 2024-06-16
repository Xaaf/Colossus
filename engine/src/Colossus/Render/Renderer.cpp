#include "Colossus/Render/Renderer.h"
#include "Colossus/Render/Arch/OpenGL/OpenGLRenderer.h"

using namespace Colossus;

Renderer* Renderer::m_Instance = nullptr;
std::shared_ptr<RendererInterface> Renderer::m_Renderer = nullptr;

Renderer* Renderer::getInstance() {
    if (m_Instance == nullptr) {
        LOG_TRACE("Renderer",
                  "m_Instance is a nullptr, creating a new instance...");
        m_Instance = new Renderer();
    }

    return m_Instance;
}

bool Renderer::createRenderer(RendererType type) {
    switch (type) {
        case RendererType::OpenGL:
            m_Renderer = std::make_shared<OpenGLRenderer>();
            m_Renderer->initialise();

            return true;
        default:
            LOG_ERROR("Renderer", "Unknown RendererType supplied!");
            return false;
    }
}

std::shared_ptr<RendererInterface> Renderer::getRenderer() {
    return m_Renderer;
}

RendererType Renderer::stringToRenderType(const std::string& renderer) {
    // Check for Vulkan, DirectX, etc.
    if (renderer != "OpenGL") {
        LOG_INFO("Renderer", "No renderer found for '"
                                 << renderer << "'. Defaulting to OpenGL.");
    }

    return RendererType::OpenGL;
}
