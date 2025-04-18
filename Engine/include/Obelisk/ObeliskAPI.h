#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Renderer/Window.h"

namespace Obelisk {
class OBELISK_API ObeliskAPI {
    private:
        static ObeliskAPI* s_Instance;

        Window* m_Window;

    public:
        static ObeliskAPI& Get();

        void Init(int width = 640, int height = 480, const char* title = "Obelisk");
        void Run();
        void Shutdown();

    private:
        ObeliskAPI() = default;
        ~ObeliskAPI() = default;
};
}