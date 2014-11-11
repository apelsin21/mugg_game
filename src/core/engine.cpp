#include "core/engine.hpp"

mugg::core::Engine::Engine() {
    this->context = nullptr;

    //OpenGL context minimum values
    this->depthBits = 24;
    this->stencilBits = 8;
    this->msaaLvl = 0;
    this->majorVer = 3;
    this->minorVer = 0;
}
mugg::core::Engine::~Engine() {
	if(this->context != nullptr) {
		delete this->context;
	}
}

bool mugg::core::Engine::Initialize() {	
    sf::ContextSettings settings(this->depthBits, this->stencilBits, this->msaaLvl, this->majorVer, this->minorVer);
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
