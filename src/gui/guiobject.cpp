#include "gui/guiobject.hpp"

mugg::gui::GUIObject::GUIObject(mugg::gui::GUIManager* parent) {
    this->parent = parent;
    this->index = 0;
    this->rotation = 0.0f;
    this->scale = glm::vec2(1.0f, 1.0f);
    this->changed = false;
}
mugg::gui::GUIManager* mugg::gui::GUIObject::GetParent() {
    return this->parent;
}

void mugg::gui::GUIObject::SetScale(const glm::vec2& scale) {
    this->scale = scale;
    
    this->scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(this->scale.x, this->scale.y, 0.0f));
    this->changed = true;
    this->parent->UpdateSprite(this->index);
}
glm::vec2 mugg::gui::GUIObject::GetScale() {
    return this->scale;
}

void mugg::gui::GUIObject::SetRotation(const float rotation) {
    this->rotation = rotation;

    this->rotationMatrix = glm::rotate(glm::mat4(1.0f), this->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    this->changed = true;
    this->parent->UpdateSprite(this->index);
}
float mugg::gui::GUIObject::GetRotation() {
    return this->rotation;
}

void mugg::gui::GUIObject::SetPosition(const glm::vec2& position) {
    this->position = position;

    this->translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->position.x, this->position.y, 0.0f));
    this->changed = true;
    this->parent->UpdateSprite(this->index);
}
glm::vec2 mugg::gui::GUIObject::GetPosition() {
    return this->position;
}

void mugg::gui::GUIObject::SetTexture(mugg::graphics::Texture2D* texture) {
    this->texture = texture;
    this->changed = true;
}
mugg::graphics::Texture2D* mugg::gui::GUIObject::GetTexture() {
    return this->texture;

}

void mugg::gui::GUIObject::SetModelMatrix(const glm::mat4& matrix) {
    this->modelMatrix = matrix;
    this->parent->UpdateSprite(this->index);
}
glm::mat4 mugg::gui::GUIObject::GetModelMatrix() {
    if(this->changed) {
        this->modelMatrix = this->translationMatrix * this->rotationMatrix * this->scaleMatrix;
        return this->modelMatrix;
    } else {
       return this->modelMatrix;
    }
}

void mugg::gui::GUIObject::SetIndex(unsigned int i) {
    this->index = i;
}
unsigned int mugg::gui::GUIObject::GetIndex() {
    return this->index;
}

bool mugg::gui::GUIObject::HasChanged() {
    return this->changed;
}
