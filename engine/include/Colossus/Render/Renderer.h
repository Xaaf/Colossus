#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include "Colossus/Render/RendererInterface.h"

namespace Colossus {
enum class RendererType {
    OpenGL,
    // Others
};

class Renderer {
    private:
        static std::shared_ptr<RendererInterface> m_Renderer;

        static Renderer* m_Instance;

    private:
        Renderer() = default;

    public:
        static Renderer* getInstance();
        static std::shared_ptr<RendererInterface> getRenderer();

        static bool createRenderer(RendererType type);
        static RendererType stringToRenderType(const std::string& renderer);
};
}  // namespace Colossus

#endif  // RENDERER_H
