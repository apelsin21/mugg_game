#ifndef FONT_HPP
#define FONT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "gui/glyph.hpp"

namespace mugg {
    namespace gui {
        class GUIManager;


        class Font {
            private:
            
                struct character_info {
                    float ax; // advance.x
                    float ay; // advance.y
                    
                    float bw; // bitmap.width;
                    float bh; // bitmap.rows;
                    
                    float bl; // bitmap_left;
                    float bt; // bitmap_top;
                    
                    float tx; // x offset of glyph in texture coordinates
                } c[128];
                
                mugg::gui::GUIManager* parent;
                GLuint textureID;
    
                FT_Library ft;
                FT_Face face;
                FT_GlyphSlot g;

                int width, height;
                unsigned int pixelSize;
                
                std::vector<Glyph> glyphs;
            public:
                Font(GUIManager*);
                ~Font();

                virtual bool Load(const std::string&, unsigned int);

                virtual GLuint GetTextureID();
                virtual void SetTextureID(GLuint);

                virtual unsigned int GetPixelSize();
                virtual int GetWidth();
                virtual int GetHeight();
        };
    }
}

#endif
