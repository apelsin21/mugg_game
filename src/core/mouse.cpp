#include "core/mouse.hpp"
#include "core/engine.hpp"

mugg::core::Mouse::Mouse(Engine* parent) {
    this->parent = parent;
}
mugg::core::Mouse::~Mouse() {
}

glm::vec2 mugg::core::Mouse::GetGlobalPosition() {
    sf::Vector2i pos = sf::Mouse::getPosition();

    return glm::vec2(pos.x, pos.y);
}
glm::vec2 mugg::core::Mouse::GetRelativePosition() {
    sf::Vector2i pos = sf::Mouse::getPosition(this->parent->GetWindow()->GetInternalHandle());

    return glm::vec2(pos.x, pos.y);
}

bool mugg::core::Mouse::IsButtonDown(mugg::core::MouseButton button) {
    return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}
