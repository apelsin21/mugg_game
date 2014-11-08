#ifndef GAME_HPP
#define GAME_HPP

#include "core/engine.hpp"
#include "core/window.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"
#include "core/logger.hpp" 

#include "gui/guimanager.hpp"

#include "scene/scenemanager.hpp"

#include "game/gamestate.hpp"

#include "graphics/color.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <string>
#include <ctime>
#include <cstdlib>

namespace mugg {
    namespace game {
        class Game {
            private:
                mugg::core::Engine* engine;
                mugg::core::Keyboard* keyboard;
                mugg::core::Mouse* mouse;
                mugg::core::Window* window;

                mugg::scene::SceneManager* sceneManager;
                
                mugg::gui::GUIManager* guiManager;

                mugg::game::GameState currentState;

                const std::string windowTitle = "Mugg Game"; 
            
                bool shouldClose;

                void Intro();
                void MainMenu();
                void RenderGame();
                void Exit();
            public:
                Game();
                ~Game();
        
                bool Start();
                
                bool ShouldClose();
                void Run();
        };
    }
}

#endif
