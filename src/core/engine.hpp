#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>

#include <SFML/Window/Context.hpp>

#include "window.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"

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

                //OpenGL context settings
                unsigned int majorVer, minorVer, msaaLvl, depthBits, stencilBits;

                sf::Context* context;
            public:
                Engine();
                ~Engine();

                bool InitializeGLContext(unsigned int, unsigned int, unsigned int, unsigned int);

                //OpenGL context values that we got from the GL implementation
                std::string GetRendererString();
                std::string GetGLVendorString();
                int GetGLMajorVer();
                int GetGLMinorVer();

                mugg::scene::SceneManager* CreateSceneManager();
                mugg::scene::SceneManager* GetSceneManager();

                mugg::gui::GUIManager* CreateGUIManager();
                mugg::gui::GUIManager* GetGUIManager();

                mugg::core::ContentManager* CreateContentManager();
                mugg::core::ContentManager* GetContentManager();
        };
    }
}

#endif
