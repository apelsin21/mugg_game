#include "gui/guimanager.hpp"
#include "gui/sprite.hpp"
#include "core/engine.hpp"

mugg::gui::GUIManager::GUIManager(mugg::core::Engine* parent) {
    this->parent = parent;

    mugg::core::Log(mugg::core::LogLevel::Info, "Creating GUIManager instance");

    this->vaoID = -1;

    this->posLocation = 1;

    //THIS IS AN UNREADABLE MESS
    //TODO: Put code into functions, this is retarded

    this->vertexShader = new mugg::graphics::Shader(graphics::ShaderType::VertexShader, true);
    this->fragmentShader = new mugg::graphics::Shader(graphics::ShaderType::FragmentShader, true);
    this->shaderProgram = new mugg::graphics::ShaderProgram(true);

    this->vertexShader->SetData(this->vertexShaderSrc);
    this->fragmentShader->SetData(this->fragmentShaderSrc);
    
    this->vertexShader->Compile();
    this->fragmentShader->Compile();
    
    this->shaderProgram->AttachShader(this->vertexShader);
    this->shaderProgram->AttachShader(this->fragmentShader);
    this->shaderProgram->Link();
    
    this->posAttribName                 = "v_position";
    this->uvAttribName                  = "v_uv";
    this->modelAttribName               = "v_model";
    this->projectionMatrixUniformName   = "u_projection";

    this->posLocation   = this->shaderProgram->GetAttrib(this->posAttribName);
    this->uvLocation    = this->shaderProgram->GetAttrib(this->uvAttribName);
    this->modelLocation = this->shaderProgram->GetAttrib(this->modelAttribName);
    this->projectionMatrixUniformLocation = this->shaderProgram->GetUniform(this->projectionMatrixUniformName);

    glGenVertexArrays(1, &this->vaoID);

    static const float vertex_positions[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 
    };
    static const float vertex_uvs[] = {
        0.0f, 0.0f, //BOTTOM LEFT
        1.0f, 1.0f, //TOP RIGHT
        0.0f, 1.0f, //TOP LEFT
        0.0f, 0.0f, //BOTTOM LEFT
        1.0f, 0.0f, //BOTTOM RIGHT
        1.0f, 1.0f, //TOP RIGHT
    };

    glBindVertexArray(this->vaoID);

    glGenBuffers(1, &this->positionBufferID);
    glGenBuffers(1, &this->uvBufferID);

    glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

    glVertexAttribPointer(this->posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(this->posLocation);

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_uvs), vertex_uvs, GL_STATIC_DRAW);

    glVertexAttribPointer(this->uvLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(this->uvLocation);
    
    glDisableVertexAttribArray(this->posLocation);
    glDisableVertexAttribArray(this->uvLocation);
}

mugg::gui::GUIManager::~GUIManager() {
    mugg::core::Log(mugg::core::LogLevel::Info, "Deleting GUIManager instance");

    this->shaderProgram->DeleteID();
    this->vertexShader->DeleteID();
    this->fragmentShader->DeleteID();

    delete this->shaderProgram;
    delete this->vertexShader;
    delete this->fragmentShader;

    for(unsigned int i = 0; i < this->sprites.size(); i++) {
        if(this->sprites[i] != nullptr) {
            delete this->sprites[i];
        }
    }
    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {
        if(this->spriteBatches[i] != nullptr) {
            delete this->spriteBatches[i];
        }
    }

    glDeleteVertexArrays(1, &this->vaoID);
}

void mugg::gui::GUIManager::UpdateSpriteBatches() {
    if(!this->spriteBatches.empty()) {
        unsigned int index = this->spriteBatches.size() - 1;
        std::size_t currentSize = this->spriteBatches[index]->GetSpriteCount();
        std::size_t maxSize = this->spriteBatches[index]->GetMaxSprites();
        
        if(currentSize >= maxSize) {
            this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->modelLocation));
        }
    } else {
        this->spriteBatches.push_back(new mugg::gui::SpriteBatch(this, 10000, this->vaoID, this->modelLocation));
    }
}

mugg::gui::Sprite* mugg::gui::GUIManager::CreateSprite() {
    Sprite* sprite = new Sprite(this);
   
    this->UpdateSpriteBatches();
    this->spriteBatches[this->spriteBatches.size() - 1]->AddSprite(sprite);
    this->sprites.push_back(sprite);

    return sprite;
}
void mugg::gui::GUIManager::UpdateSprite(unsigned int index) {
    if(index <= this->sprites.size()) {
        this->spritesToBeUpdated.push_back(index);
    }
}
std::size_t mugg::gui::GUIManager::GetNumberOfSprites() {
    return this->sprites.size();
}
bool mugg::gui::GUIManager::GetSpriteByIndex(int index, mugg::gui::Sprite*& out_image) {
    if(index < 0 || index >= this->sprites.size() || this->sprites.empty()) {
        std::cout << "Tried to get image from GUIManager by out of binds index!\n";
        return false;
    }

    out_image = this->sprites[index];
    return true;
}

mugg::gui::SpriteBatch* mugg::gui::GUIManager::CreateSpriteBatch() {
    this->UpdateSpriteBatches();

    return this->spriteBatches[this->spriteBatches.size() - 1];
}

mugg::graphics::ShaderProgram* mugg::gui::GUIManager::GetShaderProgram() {
    return this->shaderProgram;
}
void mugg::gui::GUIManager::SetShaderProgram(mugg::graphics::ShaderProgram* program) {
    this->shaderProgram = program;
}

glm::mat4 mugg::gui::GUIManager::GetProjectionMatrix() {
    return this->projectionMatrix;
}
void mugg::gui::GUIManager::SetProjectionMatrix(const glm::mat4& mat) {
    this->projectionMatrix = mat;
}

void mugg::gui::GUIManager::Render() {
    this->shaderProgram->Use();
    glBindVertexArray(this->vaoID);

    glEnableVertexAttribArray(this->posLocation);
    glEnableVertexAttribArray(this->uvLocation);
    for(unsigned int i = 0; i <= 4; i++)
        glEnableVertexAttribArray(i + this->modelLocation); 

    glm::vec2 res = this->parent->GetWindow()->GetResolution();

    this->projectionMatrix = glm::ortho<float>(0.0f, res.x, res.y, 0.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(this->projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

    for(unsigned int i = 0; i < this->spriteBatches.size(); i++) {    
        for(unsigned int u = 0; u < this->spritesToBeUpdated.size(); u++) {
            this->spriteBatches[i]->UpdateSprite(this->sprites[this->spritesToBeUpdated[u]]);
            this->spritesToBeUpdated.erase(this->spritesToBeUpdated.begin() + u);
            u--;
        }

        this->spriteBatches[i]->Render();
    }
}
