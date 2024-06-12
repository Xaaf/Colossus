#include "game/GameLogic.h"
#include <iostream>
#include "colossus/Engine.h"

using namespace Game;

Colossus::Engine* engine = Colossus::Engine::getInstance();

void GameLogic::run() {
    engine->initialise("Heroes of Colossus");
    engine->mainLoop();
}