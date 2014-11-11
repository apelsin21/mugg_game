#include "core/engine.hpp"

mugg::core::Engine::Engine() {
    Log(LogLevel::Info, "Creating engine instance");

    this->guiManager = nullptr;
    this->guiManager = nullptr;
    this->sceneManager = nullptr;
    this->context = nullptr;

    //OpenGL context minimum values
    this->depthBits = 24;
    this->stencilBits = 8;
    this->msaaLvl = 0;
    this->majorVer = 3;
    this->minorVer = 0;
}
mugg::core::Engine::~Engine() {
    Log(LogLevel::Info, "Deleting engine instance");

	if(this->context != nullptr) {
		delete this->context;
	}
}

bool mugg::core::Engine::InitializeGLContext(unsigned int depthBits,
                    unsigned int stencilBits, unsigned int majorVer, unsigned int minorVer) {
	
    sf::ContextSettings settings(depthBits, stencilBits, this->msaaLvl, majorVer, minorVer);
	this->context = new sf::Context(settings, 800, 600);
	
	//Initialize GLEW
    //experimental mode is needed for some function pointers to be initialized
    glewExperimental = GL_TRUE;
    int error = glewInit();
    if(error != GLEW_OK) {
        std::string errorString = "GLEW failed to initialize, error:\n";
        errorString += (const char*)glewGetErrorString(error);

        Log(LogLevel::Error, errorString);
        return false;
    }

	return true;
}

std::string mugg::core::Engine::GetRendererString() {
    return (const char*)glGetString(GL_RENDERER);
}
std::string mugg::core::Engine::GetGLVendorString() {
    return (const char*)glGetString(GL_VENDOR);
}
int mugg::core::Engine::GetGLMajorVer() {
    int majorVer = 0;

    glGetIntegerv(GL_MAJOR_VERSION, &majorVer);

    return majorVer;
}
int mugg::core::Engine::GetGLMinorVer() {
    int minorVer = 0;

    glGetIntegerv(GL_MINOR_VERSION, &minorVer);

    return minorVer;
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

mugg::scene::SceneManager* mugg::core::Engine::CreateSceneManager() {
    if(this->sceneManager == nullptr) {
        this->sceneManager = new mugg::scene::SceneManager(this);
    }

    return this->sceneManager;
}
mugg::scene::SceneManager* mugg::core::Engine::GetSceneManager() {
    return this->sceneManager;
}
