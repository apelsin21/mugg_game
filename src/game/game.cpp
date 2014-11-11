#include "game/game.hpp"

mugg::game::Game::Game() {
    this->engine = nullptr;
    this->keyboard = nullptr;
    this->mouse = nullptr;
    this->window = nullptr;
    this->sceneManager = nullptr;
    this->guiManager = nullptr;

    this->currentState = GameState::Intro;

    this->shouldClose = false;
}
mugg::game::Game::~Game() {
    if(this->engine) {
        delete this->engine;
    }
    if(this->keyboard) {
        delete this->keyboard;
    }
    if(this->mouse) {
        delete this->mouse;
    }
    if(this->window) {
        delete this->window;
    }
    if(this->sceneManager) {
        delete this->sceneManager;
    }
    if(this->guiManager) {
        delete this->guiManager;
    }
}

bool mugg::game::Game::Start() {
    this->engine = new mugg::core::Engine();

    if(!this->engine) {
        mugg::core::Log(mugg::core::LogLevel::Error, "Failed to create engine, exiting");
        return false;
    }

    this->keyboard = new mugg::core::Keyboard();

    if(!this->keyboard) {
        mugg::core::Log(mugg::core::LogLevel::Error, "Failed to create keyboard, exiting");
        return false;
    }
    
    this->mouse = new mugg::core::Mouse();

    if(!this->mouse) {
        mugg::core::Log(mugg::core::LogLevel::Error, "Failed to create mouse, exiting");
        return false;
    }
    
    this->window = new mugg::core::Window(glm::vec2(800, 600), this->windowTitle);

    if(!this->window) {
        mugg::core::Log(mugg::core::LogLevel::Error, "Failed to create window, exiting");
        return false;
    }
    
    //this->sceneManager = this->engine->CreateSceneManager();

    //if(!this->sceneManager) {
    //    mugg::core::Log(mugg::core::LogLevel::Error, "Failed to create SceneManager, exiting");
    //    return false;
    //}
    
    //this->guiManager = this->engine->CreateGUIManager();

    //if(!this->guiManager) {
    //    mugg::core::Log(mugg::core::LogLevel::Error, "Failed to create GUIManager, exiting");
    //    return false;
    //}

    srand(static_cast<unsigned>(time(0)));

    return true;
}

bool mugg::game::Game::ShouldClose() {
    return this->shouldClose;
}
void mugg::game::Game::Run() {
    if(this->keyboard->IsKeyDown(this->window, mugg::core::Key::Escape)) {
        this->currentState = GameState::Exit;
    }

    switch(this->currentState) {
        case GameState::Intro:
            this->Intro();
            break;
        case GameState::MainMenu:
            this->MainMenu();
            break;
        case GameState::InGame:
            this->RenderGame();
            break;
        case GameState::Exit:
            this->Exit();
            break;
        default:
            mugg::core::Log(mugg::core::LogLevel::Warning, "Reached unhandled game state");
            this->currentState = GameState::Exit;
            break;
    }

    this->window->SwapBuffers();
}

void mugg::game::Game::Intro() {
    this->currentState = GameState::MainMenu;

    //if(!this->sceneManager->Initialize()) {
    //    mugg::core::Log(mugg::core::LogLevel::Error, "SceneManager failed to initialize!");
    //}
}
void mugg::game::Game::MainMenu() {
    this->currentState = GameState::InGame;
}
void mugg::game::Game::RenderGame() {
    if(this->keyboard->IsKeyDown(this->window, mugg::core::Key::Space)) {
        float r = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
        float g = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
        float b = static_cast<float>(rand() / static_cast<float>(RAND_MAX));

        this->window->SetBackgroundColor(mugg::graphics::Color(r, g, b, 1.0f));
    }
}
void mugg::game::Game::Exit() {
    this->window->Close();

    this->shouldClose = true;
}
