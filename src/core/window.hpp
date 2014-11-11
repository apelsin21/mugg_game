#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>

#include "core/logger.hpp"
#include "graphics/color.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace mugg {
    namespace core {
        class Window {
            private:
                glm::vec2 resolution;
                std::string title;
                bool open, focused;

                sf::Window internalHandle;

                mugg::graphics::Color backgroundColor;
            public:
                Window(const glm::vec2&, const std::string&);
                ~Window();

                bool HasFocus();

                bool IsOpen();
                void Close();

                void SetTitle(const std::string&);
                std::string GetTitle();

                void SetResolution(const glm::vec2&);
                glm::vec2 GetResolution();

                void SetBackgroundColor(const mugg::graphics::Color&);
                mugg::graphics::Color GetBackgroundColor();

                sf::Window& GetInternalHandle();

                void SwapBuffers();
        };
    }
}

#endif
