#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Colossus/Rendering/RendererInterface.h"
#include "cspch.h"

namespace Colossus {
class OpenGLRenderer : public RendererInterface {
    public:
        virtual bool initialise() override;
        virtual void render() override;
};
}  // namespace Colossus

#endif  // OPENGLRENDERER_H
