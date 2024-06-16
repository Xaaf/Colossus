#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "Colossus/Render/Renderer.h"
#include "Colossus/Render/RendererInterface.h"
#include "cspch.h"

namespace Colossus {
class Window {
    public:
        Window(std::string window_name, int width, int height,
               RendererType rendererType);
        ~Window();

        void create();
        void update();
        void close();
        void stop();
};
}  // namespace Colossus

#endif  // WINDOW_H
