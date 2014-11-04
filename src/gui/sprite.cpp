#include "gui/sprite.hpp"
#include "gui/guimanager.hpp"

mugg::gui::Sprite::Sprite(mugg::gui::GUIManager* creator) : GUIObject(creator) {
    this->uvs = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    this->colors = {
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
       1.0f, 1.0f, 1.0f,
    };

    this->positionChanged = true;
    this->colorChanged = true;
    this->uvChanged = true;
}
mugg::gui::Sprite::~Sprite() {
}

bool mugg::gui::Sprite::IsPositionChanged() {
    return this->positionChanged;
}
bool mugg::gui::Sprite::IsUVChanged() {
    return this->uvChanged;
}
bool mugg::gui::Sprite::IsColorChanged() {
    return this->colorChanged;
}

std::vector<float> mugg::gui::Sprite::GetPositions() {
    return this->positions;
}
void mugg::gui::Sprite::SetPositions(const std::vector<float>& positions) {
    this->positions = positions;
}
std::vector<float> mugg::gui::Sprite::GetUVs() {
    return this->uvs;
}
void mugg::gui::Sprite::SetUVs(const std::vector<float>& uvs) {
    this->uvs = uvs;
}
std::vector<float> mugg::gui::Sprite::GetColors() {
    return this->colors;
}
void mugg::gui::Sprite::SetColors(const std::vector<float>& colors) {
    this->colors = colors;
}
