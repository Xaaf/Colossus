#include "Game/GameLogic.h"
#include "Colossus/Render/RendererFactory.h"

using namespace Game;

void GameLogic::setup() {
    engine = Colossus::Engine::getInstance();
    engine->initialise("Heroes of Colossus", Colossus::RendererType::OpenGL);

    run();
}

void GameLogic::run() {
    while (engine->isRunning()) {
        engine->step();
    }
}