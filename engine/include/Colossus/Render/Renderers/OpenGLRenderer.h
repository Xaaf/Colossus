#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Colossus/Render/RendererInterface.h"
#include "cspch.h"

namespace Colossus {
class OpenGLRenderer : public RendererInterface {
    private:
        GLFWwindow* m_Window;

        std::string m_WindowName;
        int m_Width;
        int m_Height;

    public:
        bool initialise() override;
        bool create() override;
        void render() override;
        void stop() override;
};
}  // namespace Colossus

#endif  // OPENGLRENDERER_H
