#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <iostream>
#include <vector>

#include <SFML/Window/Keyboard.hpp>

#include "core/keydefs.hpp"

namespace mugg {
    namespace core {
        class Keyboard {
            private:
            public:
                Keyboard();
                ~Keyboard();
                
                bool IsKeyDown(mugg::core::Key);
        };
        
        
    }
}

#endif
