#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>

#include <SFML/Window/Context.hpp>

#include "core/logger.hpp"

namespace mugg {
    namespace core {
        class Engine {
            private:
                //OpenGL context settings
                unsigned int majorVer, minorVer, msaaLvl, depthBits, stencilBits;

                sf::Context* context;
            public:
                Engine();
                ~Engine();

                bool Initialize();

                //OpenGL context values that we got from the GL implementation
                std::string GetRendererString();
                std::string GetGLVendorString();
                int GetGLMajorVer();
                int GetGLMinorVer();
        };
    }
}

#endif
