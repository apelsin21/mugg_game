#include "core/engine.hpp"

mugg::core::Engine::Engine(bool createContext) {
    Log(LogLevel::Info, "Creating engine instance");

    if(createContext) {
        sf::ContextSettings settings(this->depthBits,
                            this->stencilBits,
                            this->msaa,
                            this->majorVersion,
                            this->minorVersion);

        this->context = new sf::Context(settings, 800, 600);
        
        int error = glewInit();
        if(error != GLEW_OK) {
            std::string errorString = "GLEW failed to initialize, error:\n";
            errorString += (const char*)glewGetErrorString(error);
            Log(LogLevel::Error, errorString);
        }
    }
}
mugg::core::Engine::~Engine() {
    Log(LogLevel::Info, "Deleting engine instance");
}

mugg::gui::GUIManager* mugg::core::Engine::CreateGUIManager() {
    if(this->guiManager != nullptr) {
        this->guiManager = new mugg::gui::GUIManager(this);
    }

    return this->guiManager;
}
mugg::gui::GUIManager* mugg::core::Engine::GetGUIManager() {
    return this->guiManager;
}

mugg::core::ContentManager* mugg::core::Engine::CreateContentManager() {
    if(this->contentManager != nullptr) {
        this->contentManager = new mugg::core::ContentManager(this);
    }

    return this->contentManager;
}
mugg::core::ContentManager* mugg::core::Engine::GetContentManager() {
    return this->contentManager;    
}

mugg::core::Window* mugg::core::Engine::CreateWindow(const glm::vec2& resolution, const std::string& title) {
    if(this->window != nullptr) {
        this->window = new mugg::core::Window(this, resolution, title);
    }

    return this->window;
}
mugg::core::Window* mugg::core::Engine::GetWindow() {
    return this->window;
}

mugg::core::Keyboard* mugg::core::Engine::CreateKeyboard() {
    if(this->keyboard  != nullptr) {
        this->keyboard = new mugg::core::Keyboard(this);
    }

    return this->keyboard;
}
mugg::core::Keyboard* mugg::core::Engine::GetKeyboard() {
    return this->keyboard;
}

mugg::core::Mouse* mugg::core::Engine::CreateMouse() {
    if(this->mouse != nullptr) {
        this->mouse = new mugg::core::Mouse(this);
    }

    return this->mouse;
}
mugg::core::Mouse* mugg::core::Engine::GetMouse() {
    return this->mouse;
}

mugg::scene::SceneManager* mugg::core::Engine::CreateSceneManager() {
    if(this->sceneManager != nullptr) {
        this->sceneManager = new mugg::scene::SceneManager(this);
    }

    return this->sceneManager;
}
mugg::scene::SceneManager* mugg::core::Engine::GetSceneManager() {
    return this->sceneManager;
}
