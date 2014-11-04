#ifndef TEXTUREATLAS_HPP
#define TEXTUREATLAS_HPP

#include "graphics/texture2d.hpp"

namespace mugg {
    namespace core {
        class ContentManager;
    }

    namespace graphics {
        class TextureAtlas : public Texture2D {
            private:
                int offset;
     
                mugg::core::ContentManager* parent;
            public:
                TextureAtlas(mugg::core::ContentManager*);
                ~TextureAtlas();

                virtual void SetOffset(int);
                virtual int GetOffset();
        };
    }
}

#endif
