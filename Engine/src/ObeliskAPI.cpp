#include "Obelisk/ObeliskAPI.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <utility>

namespace Obelisk {
ObeliskAPI* ObeliskAPI::s_Instance = nullptr;

ObeliskAPI& ObeliskAPI::Get() {
    if (!s_Instance) s_Instance = new ObeliskAPI();

    return *s_Instance;
}

void ObeliskAPI::SetInitCallback(std::function<void()> callback) {
    m_InitCallback = std::move(callback);
}

void ObeliskAPI::SetUpdateCallback(std::function<void()> callback) {
    m_UpdateCallback = std::move(callback);
}

void ObeliskAPI::SetShutdownCallback(std::function<void()> callback) {
    m_ShutdownCallback = std::move(callback);
}

void ObeliskAPI::Init(int width, int height, const char* title) {
    LOG_INFO("Initializing Obelisk Engine...");

    m_Window = new Window();
    if (!m_Window->Create(1280, 720, "Heroes of Colossus")) {
        LOG_ERROR("Failed to create window!");
    }

    if (m_InitCallback) {
        m_InitCallback();
    }

    LOG_INFO("Finished initializing Obelisk Engine!");
}

void ObeliskAPI::Run() {
    LOG_INFO("Running Obelisk Engine...");

    while (!m_Window->ShouldClose()) {
        if (m_UpdateCallback) {
            m_UpdateCallback();
        }

        m_Window->Tick();
    }
}

void ObeliskAPI::Shutdown() {
    LOG_INFO("Shutting down Obelisk Engine...");

    if (m_Window) {
        delete m_Window;
        m_Window = nullptr;
    }
    glfwTerminate();

    if (m_ShutdownCallback) {
        m_ShutdownCallback();
    }
}
}  // namespace Obelisk