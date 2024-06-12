#include "Game/GameLogic.h"
#include "Colossus/Engine.h"
#include "Colossus/Rendering/RendererFactory.h"

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