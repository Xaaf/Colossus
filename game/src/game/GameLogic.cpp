#include "game/GameLogic.h"
#include "colossus/Engine.h"
#include "colossus/rendering/RendererFactory.h"

using namespace Game;

Colossus::Engine* engine = Colossus::Engine::getInstance();


void GameLogic::setup() {

}

void GameLogic::run() {
    engine->initialise("Heroes of Colossus", Colossus::RendererType::OpenGL);

    while (engine->isRunning()) {
        engine->step();
    }
}