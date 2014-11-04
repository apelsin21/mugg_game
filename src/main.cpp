#include "core/engine.hpp"
#include "core/window.hpp"
#include "core/keyboard.hpp"
#include "core/mouse.hpp"

#include "gui/guimanager.hpp"
#include "gui/sprite.hpp"

#include <glm/glm.hpp>

#include "core/logger.hpp"

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

    Mesh* testMesh = contentManager->CreateMesh("data/models/complexshape.nff");

    if(!testMesh) {
        Log(LogLevel::Error, "Failed to load mesh " + testMesh->GetFilepath());
    } else {
        std::cout << "Successfully loaded mesh " << testMesh->GetFilepath()
                << " which has " << testMesh->GetVertexCount() <<
                " vertices and " << testMesh->GetNormalCount() << " normals.\n";
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
