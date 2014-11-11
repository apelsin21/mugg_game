#include "core/keyboard.hpp"

mugg::core::Keyboard::Keyboard() {
}
mugg::core::Keyboard::~Keyboard() {
}

bool mugg::core::Keyboard::IsKeyDown(mugg::core::Key key) {
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}
