#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <iostream>
#include <vector>

#include <SFML/Window/Keyboard.hpp>

#include "core/keydefs.hpp"
#include "core/window.hpp"

namespace mugg {
    namespace core {
        class Keyboard {
            private:
            public:
                Keyboard();
                ~Keyboard();
                
                bool IsKeyDown(mugg::core::Window&, mugg::core::Key);
                bool IsKeyDown(mugg::core::Window*, mugg::core::Key);
        };
        
        
    }
}

#endif
