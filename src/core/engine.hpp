#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>

#include <SFML/Window/Context.hpp>

#include "window.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"
#include "core/contentmanager.hpp"

#include "gui/guimanager.hpp"

#include "scene/scenemanager.hpp"

#include "core/logger.hpp"

namespace mugg {
    namespace core {
        class Engine {
            private:
                mugg::gui::GUIManager* guiManager;
                mugg::core::ContentManager* contentManager;
                mugg::scene::SceneManager* sceneManager;

                mugg::core::Window* window;
                mugg::core::Keyboard* keyboard;
                mugg::core::Mouse* mouse;

                //OpenGL context settings
                const unsigned int depthBits    = 24;
                const unsigned int stencilBits  = 8;
                const unsigned int msaa         = 0;
                const unsigned int majorVersion = 3;
                const unsigned int minorVersion = 3;

                sf::Context* context;
            public:
                Engine(bool);
                ~Engine();

                mugg::core::Window* CreateWindow(const glm::vec2&, const std::string&);
                mugg::core::Window* GetWindow();

                mugg::core::Keyboard* CreateKeyboard();
                mugg::core::Keyboard* GetKeyboard();

                mugg::core::Mouse* CreateMouse();
                mugg::core::Mouse* GetMouse();

                mugg::scene::SceneManager* CreateSceneManager();
                mugg::scene::SceneManager* GetSceneManager();

                mugg::gui::GUIManager* CreateGUIManager();
                mugg::gui::GUIManager* GetGUIManager();

                mugg::core::ContentManager* CreateContentManager();
                mugg::core::ContentManager* GetContentManager();

                sf::Context GetContextSettings();
        };
    }
}

#endif
