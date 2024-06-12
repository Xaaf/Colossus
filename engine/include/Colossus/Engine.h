#ifndef ENGINE_H
#define ENGINE_H

#include "Colossus/Render/RendererFactory.h"
#include "Colossus/Render/RendererInterface.h"
#include "Colossus/Render/Window.h"

namespace Colossus {
class Engine {
    private:
//        std::unique_ptr<RendererInterface> renderer;
        Window* m_Window;

        bool m_IsRunning;

        static Engine* instance;

    private:
        Engine();
        ~Engine();

    public:
        static Engine* getInstance();

        void initialise(const std::string& window_name, const std::string& renderer);
        void step();
        void stop();

        bool isRunning() const;
};
}  // namespace Colossus

#endif  // ENGINE_H