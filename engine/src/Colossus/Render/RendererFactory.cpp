#include "Colossus/Render/RendererFactory.h"
#include "Colossus/Render/Renderers/OpenGLRenderer.h"

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
