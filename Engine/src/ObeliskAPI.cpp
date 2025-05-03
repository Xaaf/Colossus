#include "Obelisk/ObeliskAPI.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Obelisk {
ObeliskAPI* ObeliskAPI::s_Instance = nullptr;

ObeliskAPI& ObeliskAPI::Get() {
    if (!s_Instance)
        s_Instance = new ObeliskAPI();

    return *s_Instance;
}

void ObeliskAPI::Init(int width, int height, const char* title) {
    LOG_INFO("Initializing Obelisk Engine...");

    m_Window = new Window();
    if (!m_Window->Create(1280, 720, "Heroes of Colossus")) {
        LOG_ERROR("Failed to create window!");
    }

    LOG_INFO("Finished initializing Obelisk Engine!");
}

void ObeliskAPI::Run() {
    LOG_INFO("Running Obelisk Engine...");

    while (!m_Window->ShouldClose()) {
        m_Window->Tick();
    }
}

void ObeliskAPI::Shutdown() {
    LOG_INFO("Shutting down Obelisk Engine...");
    delete m_Window;
}
}