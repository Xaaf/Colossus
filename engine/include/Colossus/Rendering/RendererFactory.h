#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

#include <memory>
#include "Colossus/Rendering/RendererInterface.h"

namespace Colossus {
enum class RendererType {
    OpenGL,
    // Others
};

class RendererFactory {
    public:
        static std::unique_ptr<RendererInterface> createRenderer(
            RendererType type);
};
}  // namespace Colossus

#endif  // RENDERERFACTORY_H
