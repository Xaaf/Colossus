#pragma once

#include "ObeliskPCH.h"

namespace Obelisk {
class Window {
    private:
        GLFWwindow* m_Window = nullptr;

    public:
        Window() = default;
        ~Window();

        int Create(int width, int height, std::string title);
        void Tick();

        [[nodiscard]] bool ShouldClose() const {
            return glfwWindowShouldClose(m_Window);
        };
};
}