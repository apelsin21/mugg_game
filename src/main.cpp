#include "game/game.hpp"

int main(void) {
    mugg::game::Game game;

    if(!game.Start()) {
        return -1;
    }

    while(!game.ShouldClose()) {
        game.Run(); //Kinda retarded
    }

    return 0;
}
