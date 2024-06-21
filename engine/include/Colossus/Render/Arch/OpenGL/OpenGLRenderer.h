#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <unordered_map>
#include "Colossus/Render/Mesh.h"
#include "Colossus/Render/RendererInterface.h"
#include "cspch.h"

namespace Colossus {
struct BufferIDs {
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
};

class OpenGLRenderer : public RendererInterface {
    private:
        GLFWwindow* m_Window;

        std::string m_WindowName;
        int m_Width;
        int m_Height;

        std::unordered_map<const Mesh*, BufferIDs> meshBufferMap;

    private:
        static BufferIDs createBuffers(const Mesh& mesh);

    public:
        bool initialise() override;
        bool createWindow() override;

        void render() override;
        void stop() override;

        void addMesh(const Mesh& mesh);
};
}  // namespace Colossus

#endif  // OPENGLRENDERER_H
