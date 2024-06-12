#ifndef WINDOW_H
#define WINDOW_H

#include "cspch.h"

namespace Colossus {
class Window {
    private:
        GLFWwindow* m_Window{};

        std::string m_WindowName;
        int m_Width;
        int m_Height;

    public:
        Window(std::string window_name, int width, int height);

        void create();
        void tick();
        void close();
};
}  // namespace Colossus

#endif  // WINDOW_H
