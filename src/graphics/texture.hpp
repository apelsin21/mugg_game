#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <string>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#include <FreeImage.h>

#include "core/logger.hpp"

#include "graphics/graphicsdefs.hpp"
#include "graphics/globject.hpp"

namespace mugg {
    namespace graphics {
    class Texture : public GLObject {
            private:
                //Default texture is just a 2*2 checkerboard texture
                GLfloat defaultTexture[12] = {
                    0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
                    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
                };
                
                mugg::graphics::TextureFilter minFilter;
                mugg::graphics::TextureFilter magFilter;

                mugg::graphics::TextureWrap uWrap;
                mugg::graphics::TextureWrap vWrap;

                int width, height, bpp, colorsUsed;
                std::string filepath;
                bool loaded, hasGeneratedID, mipMaps;
            public:
                Texture();
                ~Texture();

                bool Load(const std::string&, bool);

                void SetFilepath(std::string);
                std::string GetFilepath();

                void SetWidth(int);
                int GetWidth();

                void SetHeight(int);
                int GetHeight();

                void SetBPP(int);
                int GetBPP();

                void SetColorsUsed(int);
                int GetColorsUsed();
                
                void SetLoaded(bool);
                bool IsLoaded();
                void LoadDefault();
                
                void SetUsesMipMaps(bool);
                bool UsesMipMaps();
               
                mugg::graphics::TextureWrap GetUWrap();
                mugg::graphics::TextureWrap GetVWrap();

                mugg::graphics::TextureFilter GetMinFilter();
                mugg::graphics::TextureFilter GetMagFilter();
                
                void SetWrap(mugg::graphics::TextureWrap, mugg::graphics::TextureWrap);
                void SetFilter(mugg::graphics::TextureFilter, mugg::graphics::TextureFilter);

                void GenID();

                void Bind();
                void UnBind();
        };
    }
}

#endif
