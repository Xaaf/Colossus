#ifndef ENGINE_H
#define ENGINE_H

#include "Colossus/Rendering/RendererFactory.h"
#include "Colossus/System/Window.h"

namespace Colossus {
class Engine {
    private:
        Window* m_Window = nullptr;
        std::unique_ptr<RendererInterface> renderer;

        bool m_IsRunning;

        static Engine* instance;

    private:
        Engine();
        ~Engine();

    public:
        static Engine* getInstance();

        void initialise(const std::string& window_name, RendererType type);
        void step();
        void stop();

        bool isRunning() const;
};
}  // namespace Colossus

#endif  // ENGINE_H