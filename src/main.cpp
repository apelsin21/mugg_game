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
    Engine engine(true);

    //Get a handle to a window so we can use it
    Window* window = engine.CreateWindow(glm::vec2(800, 600), "Fun game hahahah");

    //Get a pointer to the keyboard, so we can do basic input
    Keyboard* keyboard = engine.CreateKeyboard();
    Mouse* mouse = engine.CreateMouse();

    //Get a handle to a content manager, so we can load resources
    ContentManager* contentManager = engine.CreateContentManager();

    SceneManager* sceneManager = engine.CreateSceneManager();

    Mesh* testMesh;

    if(!testMesh->Load("data/models/complexshape.nff")) {
        Log(LogLevel::Error, "Failed to load mesh " + testMesh->GetFilepath());
    } else {
        Log(LogLevel::Info, "Successfully loaded mesh " + testMesh->GetFilepath()
                + " which has " + std::to_string(testMesh->GetVertexCount()) +
                " vertices and " + std::to_string(testMesh->GetNormalCount()) + " normals.");
    }

    SceneNode* node = sceneManager->CreateSceneNode();
    node->AddMesh(testMesh);

    while(window->IsOpen()) {
        //Close on ESC key down
        if(keyboard->IsKeyDown(mugg::core::Key::Escape)) {
            window->Close();
        }

        sceneManager->Render();

        //You ofcourse need to swap your buffers
        window->SwapBuffers();
    }

    delete window;
    delete keyboard;
    delete mouse;
    delete contentManager;
    delete sceneManager;

    return 0;
}
