#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

namespace mugg {
    namespace game {
        enum GameState {
            Intro, //For splash screen and the like
            MainMenu, //We are in the main menu
            InGame, //When you are inside the actual game
            Exit //Currently exiting
        };
    }
}

#endif
