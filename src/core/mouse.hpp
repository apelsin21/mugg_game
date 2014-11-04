#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/Window/Mouse.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace mugg {
    namespace core {
        class Engine;

        enum MouseButton {
            mouse_left = sf::Mouse::Left,
            mouse_right = sf::Mouse::Right,
            mouse_middle = sf::Mouse::Middle,
            mouse_extra1 = sf::Mouse::XButton1,
            mouse_extra2 = sf::Mouse::XButton2
        };

        class Mouse {
            private:
                glm::vec2 position;
            
                Engine* parent;
            public:
                Mouse(Engine*);
                ~Mouse();

                glm::vec2 GetGlobalPosition();
                glm::vec2 GetRelativePosition();

                bool IsButtonDown(mugg::core::MouseButton);
        };
    }
}

#endif
