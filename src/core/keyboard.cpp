#include "core/keyboard.hpp"

mugg::core::Keyboard::Keyboard() {
}
mugg::core::Keyboard::~Keyboard() {
}

bool mugg::core::Keyboard::IsKeyDown(mugg::core::Window& window, mugg::core::Key key) {
    if(!window.HasFocus()) {
        return false;
    }
    
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}
bool mugg::core::Keyboard::IsKeyDown(mugg::core::Window* window, mugg::core::Key key) {
    if(!window->HasFocus()) {
        return false;
    }
    
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}
