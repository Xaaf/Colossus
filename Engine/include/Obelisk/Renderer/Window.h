#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Scene/Scene.h"

namespace Obelisk {
class Window {
    private:
        GLFWwindow* m_Window = nullptr;
        Scene* m_Scene = nullptr;

    public:
        Window() = default;
        ~Window();

        int Create(int width, int height, const std::string& title);
        void Tick();

        void SetScene(Scene* scene) { m_Scene = scene; };

        [[nodiscard]] bool ShouldClose() const {
            return glfwWindowShouldClose(m_Window);
        };
};
}