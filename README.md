# Colossus Engine

A modern C++20 game engine built with OpenGL, designed for performance and ease of use.

## Building

The project uses CMake for cross-platform building:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
```

## Dependencies

- **GLFW**: Window and input management
- **GLAD**: OpenGL loader
- **GLM**: Mathematics library with experimental quaternion support
- **stb_image**: Image loading for textures

## Example Usage

```cpp
#include "Obelisk/ObeliskAPI.h"
#include "Obelisk/Scene/Entity.h"
#include "Obelisk/Core/Camera.h"

// Create entities and scene
Obelisk::Scene scene;
Obelisk::Camera camera;
Obelisk::Entity cube;

void Initialize() {
    // Set up camera
    camera.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    camera.SetPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 100.0f);
    
    // Create cube entity
    auto mesh = std::make_shared<Obelisk::Mesh>(vertices, indices);
    auto shader = std::make_shared<Obelisk::Shader>("basic.vert", "basic.frag");
    auto texture = std::make_shared<Obelisk::Texture>("texture.jpg");
    
    cube = Obelisk::Entity(mesh, shader, texture);
    scene.AddEntity(&cube);
    scene.SetCamera(&camera);
}

int main() {
    auto& engine = Obelisk::ObeliskAPI::Get();
    engine.SetInitCallback(Initialize);
    
    engine.Init(1280, 720, "My Game");
    engine.Run();
    engine.Shutdown();
    
    return 0;
}
```

## Documentation

This documentation is generated using Doxygen. To build the documentation:

```bash
doxygen
```

The generated documentation will be available in the `docs/html/` directory.

## License

...
