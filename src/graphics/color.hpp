#ifndef COLOR_HPP
#define COLOR_HPP

namespace mugg {
    namespace graphics {
        class Color {
            public:
                static const Color Black;
                static const Color White;
                static const Color Red;
                static const Color Green;
                static const Color Blue;
                static const Color Yellow;
                static const Color Magenta;
                static const Color Cyan;
                static const Color Transparent;

                Color(float, float, float, float);
                Color(float, float, float);
                Color(const Color&);
                Color();
                
                float r,g,b,a;
                
                void Set(float, float, float, float);

                void Clamp();
        };
    }
}

#endif
