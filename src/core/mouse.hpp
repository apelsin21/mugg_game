#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/keydefs.hpp"
#include "core/window.hpp"

namespace mugg {
    namespace core {
        class Mouse {
            private:
                glm::vec2 position;
            public:
                Mouse();
                ~Mouse();

                glm::vec2 GetGlobalPosition();
                glm::vec2 GetRelativePosition(const sf::Window&);

                bool IsButtonDown(mugg::core::MouseButton);
        };
    }
}

#endif
