#include "Colossus/Rendering/RendererFactory.h"
#include "Colossus/Rendering/Renderers/OpenGLRenderer.h"

using namespace Colossus;

std::unique_ptr<RendererInterface> RendererFactory::createRenderer(RendererType type) {
    switch (type) {
        case RendererType::OpenGL:
            return std::make_unique<OpenGLRenderer>();
        default:
            LOG_ERROR("Renderer", "Unknown RendererType supplied!");
            return nullptr;
    }
}
