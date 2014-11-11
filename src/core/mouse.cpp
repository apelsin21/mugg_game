#include "core/mouse.hpp"

mugg::core::Mouse::Mouse() {
}
mugg::core::Mouse::~Mouse() {
}

glm::vec2 mugg::core::Mouse::GetGlobalPosition() {
    sf::Vector2i pos = sf::Mouse::getPosition();

    return glm::vec2(pos.x, pos.y);
}
glm::vec2 mugg::core::Mouse::GetRelativePosition(const sf::Window& window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);

    return glm::vec2(pos.x, pos.y);
}

bool mugg::core::Mouse::IsButtonDown(mugg::core::MouseButton button) {
    return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}
