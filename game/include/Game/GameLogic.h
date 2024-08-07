#ifndef GAME_H
#define GAME_H

#include "Colossus/Engine.h"

namespace Game {
class GameLogic {
    private:
        Colossus::Engine* engine;

    public:
        void setup(const std::string& renderer);
        void run();
};
}  // namespace Game

#endif  // GAME_H
