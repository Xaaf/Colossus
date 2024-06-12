#include "Game/GameLogic.h"
#include "Colossus/Render/RendererFactory.h"

using namespace Game;

void GameLogic::setup(const std::string& renderer) {
    engine = Colossus::Engine::getInstance();
    engine->initialise("Heroes of Colossus", renderer);

    run();
}

void GameLogic::run() {
    while (engine->isRunning()) {
        engine->step();
    }
}