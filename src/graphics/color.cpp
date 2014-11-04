#include "graphics/color.hpp"

const mugg::graphics::Color mugg::graphics::Color::Black(0.0f, 0.0f, 0.0f);
const mugg::graphics::Color mugg::graphics::Color::White(1.0f, 1.0f, 1.0f);
const mugg::graphics::Color mugg::graphics::Color::Red(1.0f, 0.0f, 0.0f);
const mugg::graphics::Color mugg::graphics::Color::Green(0.0f, 1.0f, 0.0f);
const mugg::graphics::Color mugg::graphics::Color::Blue(0.0f, 0.0f, 1.0f);
const mugg::graphics::Color mugg::graphics::Color::Yellow(1.0f, 1.0f, 0.0f);
const mugg::graphics::Color mugg::graphics::Color::Magenta(0.0f, 1.0f, 1.0f);
const mugg::graphics::Color mugg::graphics::Color::Cyan(0.0f, 1.0f, 1.0f);
const mugg::graphics::Color mugg::graphics::Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);

mugg::graphics::Color::Color(const Color& color) {
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
}
mugg::graphics::Color::Color(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->Clamp();
}
mugg::graphics::Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1.0f;
    this->Clamp();
}
mugg::graphics::Color::Color() {
    this->r = 0.0f;
    this->g = 0.0f;
    this->b = 0.0f;
    this->a = 1.0f;
}

void mugg::graphics::Color::Clamp() {
    if(r < 0.0f)
        r = 0.0f;
    else if(r > 1.0f)
        r = 1.0f;

    if(g < 0.0f)
        g = 0.0f;
    else if(g > 1.0f)
        g = 1.0f;

    if(b < 0.0f)
        b = 0.0f;
    else if(b > 1.0f)
        b = 1.0f;

    if(a < 0.0f)
        a = 0.0f;
    else if(a > 1.0f)
        a = 1.0f;
}

void mugg::graphics::Color::Set(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    this->Clamp();
}
