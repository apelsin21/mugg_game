#include "core/window.hpp"

mugg::core::Window::Window(const glm::vec2& res, const std::string& title) {
    this->focused = false;
    this->open = true;

    this->resolution = res;
    this->title = title;
    this->internalHandle.create(sf::VideoMode(this->resolution.x, this->resolution.y),
                                            this->title, sf::Style::Default);
}
mugg::core::Window::~Window() {
    Log(LogLevel::Info, "Deleting window instance");
}

bool mugg::core::Window::HasFocus() {
    return this->focused;
}

bool mugg::core::Window::IsOpen() {
    return this->open;
}
void mugg::core::Window::Close() {
    this->open = false;
    this->internalHandle.close();
}

void mugg::core::Window::SetTitle(const std::string& title) {
    this->title = title;

    this->internalHandle.setTitle(title);
}
std::string mugg::core::Window::GetTitle() {
    return this->title;
}

void mugg::core::Window::SetResolution(const glm::vec2& res) {
    this->resolution = res;

    this->internalHandle.setSize(sf::Vector2u(this->resolution.x, this->resolution.y));
    glViewport(0, 0, this->resolution.x, this->resolution.y);
}
glm::vec2 mugg::core::Window::GetResolution() {
    return this->resolution;
}

sf::Window& mugg::core::Window::GetInternalHandle() {
    return this->internalHandle;
}

void mugg::core::Window::SetBackgroundColor(const mugg::graphics::Color& color) {
    this->backgroundColor = color;
}
mugg::graphics::Color mugg::core::Window::GetBackgroundColor() {
    return this->backgroundColor;
}

void mugg::core::Window::SwapBuffers() {
    sf::Event internalEvent;

    while(this->internalHandle.pollEvent(internalEvent)) {
        switch(internalEvent.type) {
            case sf::Event::Closed:
                this->Close();
                break;
            case sf::Event::Resized:
                this->resolution = glm::vec2(internalEvent.size.width, internalEvent.size.height);
                glViewport(0, 0, this->resolution.x, this->resolution.y);
                break;
            case sf::Event::LostFocus:
                this->focused = false;
                break;
            case sf::Event::GainedFocus:
                this->focused = true;
                break;
            default:
                break;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);

    this->internalHandle.display();
}
