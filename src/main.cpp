#include "core/engine.hpp"
#include "core/window.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"

#include "gui/guimanager.hpp"
#include "gui/sprite.hpp"

#include "core/logger.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

using namespace mugg;
using namespace core;
using namespace gui;
using namespace scene;
using namespace graphics;

int main(void) {
    //Create an engine
    Engine engine;

    if(!engine.InitializeGLContext(24, 8, 3, 0)) {
        Log(LogLevel::Error, "Failed to initialize OpenGL");
        return -1;
    } else {
        std::cout << "Engine OpenGL context:"
                  << "\nVendor: " << engine.GetGLVendorString()
                  << "\nRenderer: " << engine.GetRendererString() 
                  << "\nOpenGL Version: " << engine.GetGLMajorVer() << "."
                  << engine.GetGLMinorVer() << "\n";
    }

    //Get a handle to a window so we can use it
    Window* window = engine.CreateWindow(glm::vec2(800, 600), "Mugg game");

    //Get a pointer to the keyboard, so we can do basic input
    Keyboard* keyboard = engine.CreateKeyboard();
    Mouse* mouse = engine.CreateMouse();

    //Get a handle to a content manager, so we can load resources
    ContentManager* contentManager = engine.CreateContentManager();

    Mesh* testMesh = new Mesh();

    if(!testMesh->Load("data/models/complexshape.nff")) {
        Log(LogLevel::Error, "Failed to load mesh " + testMesh->GetFilepath());
    }

    while(window->IsOpen()) {
        //Close on ESC key down
        if(keyboard->IsKeyDown(mugg::core::Key::Escape)) {
            window->Close();
        }

        //You ofcourse need to swap your buffers
        window->SwapBuffers();
    }

    delete window;
    delete keyboard;
    delete mouse;
    delete contentManager;

    return 0;
}
