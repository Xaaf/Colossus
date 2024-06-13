#include "Colossus/Render/RendererFactory.h"
#include "Colossus/Render/Arch/OpenGL/OpenGLRenderer.h"

using namespace Colossus;

std::unique_ptr<RendererInterface> RendererFactory::createRenderer(
    RendererType type) {
    switch (type) {
        case RendererType::OpenGL:
            return std::make_unique<OpenGLRenderer>();
        default:
            LOG_ERROR("Renderer", "Unknown RendererType supplied!");
            return nullptr;
    }
}
RendererType RendererFactory::stringToRenderType(const std::string& renderer) {
    // Check for Vulkan, DirectX, etc.

    if (renderer != "OpenGL") {
        LOG_INFO("RendererFactory", "No renderer found for '"
                                        << renderer
                                        << "'. Defaulting to OpenGL.");
    }

    return RendererType::OpenGL;
}
