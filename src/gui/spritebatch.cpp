#include "gui/spritebatch.hpp"
#include "gui/sprite.hpp"

mugg::gui::SpriteBatch::SpriteBatch(mugg::gui::GUIManager* parent, unsigned int maxSprites, GLuint vaoID, GLint modelMatrixLocation) {
    //Initialize default values
    this->modelMatrixBufferID = -1;
    this->texID = 1; //TODO: FIX
    this->spriteCount = 0;
    
    //Initialize member variables with parameters
    this->parent = parent;
    this->maxSprites = maxSprites;
    this->modelMatrixLocation = modelMatrixLocation;
    this->vaoID = vaoID;

    this->bufferSize = sizeof(glm::mat4) * this->maxSprites;
    this->stride = sizeof(glm::mat4);
    
    glBindVertexArray(this->vaoID);
    
    glGenBuffers(1, &this->modelMatrixBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBufferID);
    glBufferData(GL_ARRAY_BUFFER, this->bufferSize, NULL, GL_DYNAMIC_DRAW);

    for(unsigned int i = 0; i < 4; i++) {
        glVertexAttribPointer(this->modelMatrixLocation + i, 4, GL_FLOAT, GL_FALSE, this->stride, (GLvoid*)(sizeof(glm::vec4) * i));
        glEnableVertexAttribArray(this->modelMatrixLocation + i);
        //glVertexAttribDivisor(this->modelMatrixLocation + i, 1);
    }
}
mugg::gui::SpriteBatch::~SpriteBatch() {
    if(glIsBuffer(this->modelMatrixBufferID) == GL_TRUE) {
        glDeleteBuffers(1, &this->modelMatrixBufferID);
    }
}

void mugg::gui::SpriteBatch::AddSprite(mugg::gui::Sprite* sprite) {
    sprite->SetIndex(this->spriteCount);
    this->UpdateSprite(sprite);
    this->spriteCount++;
}
void mugg::gui::SpriteBatch::UpdateSprite(mugg::gui::Sprite* sprite) {
    if(sprite->GetIndex() <= this->spriteCount) {
        glBindVertexArray(this->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, this->modelMatrixBufferID);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * sprite->GetIndex(), sizeof(glm::mat4), (GLvoid*)(&sprite->GetModelMatrix()[0]));
    }
}

unsigned int mugg::gui::SpriteBatch::GetSpriteCount() {
    return this->spriteCount;
}
unsigned int mugg::gui::SpriteBatch::GetMaxSprites() {
    return this->maxSprites;
}

int mugg::gui::SpriteBatch::GetBufferSize() {
    return this->bufferSize;
}
int mugg::gui::SpriteBatch::GetStride() {
    return this->stride;
}

GLuint mugg::gui::SpriteBatch::GetModelMatrixBufferID() {
    return this->modelMatrixBufferID;
}
void mugg::gui::SpriteBatch::SetModelMatrixBufferID(GLuint id) {
    this->modelMatrixBufferID = id;
}

GLuint mugg::gui::SpriteBatch::GetTextureID() {
    return this->texID;
}
void mugg::gui::SpriteBatch::SetTextureID(GLuint id) {
    this->texID = id;
}

void mugg::gui::SpriteBatch::Render() {
    glBindTexture(GL_TEXTURE_2D, this->texID);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, this->spriteCount);
}
