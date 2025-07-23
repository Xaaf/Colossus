#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Renderer/Window.h"

namespace Obelisk {
class OBELISK_API ObeliskAPI {
    private:
        std::function<void()> m_InitCallback;
        std::function<void()> m_UpdateCallback;
        std::function<void()> m_ShutdownCallback;

        std::unique_ptr<Window> m_Window;

    public:
        static ObeliskAPI& Get();

        void SetInitCallback(std::function<void()> callback);
        void SetUpdateCallback(std::function<void()> callback);
        void SetShutdownCallback(std::function<void()> callback);

        void Init(int width = 640, int height = 480,
                  const char* title = "Obelisk");
        void Run();
        void Shutdown();

        Window* GetWindow() { return m_Window.get(); };

    private:
        ObeliskAPI() = default;
        ~ObeliskAPI() = default;
};
}  // namespace Obelisk