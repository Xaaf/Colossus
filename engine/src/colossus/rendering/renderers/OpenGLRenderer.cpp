#include "colossus/rendering/renderers/OpenGLRenderer.h"

using namespace Colossus;

bool OpenGLRenderer::initialise() {
    // Initialise
    return true;
}

void OpenGLRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}