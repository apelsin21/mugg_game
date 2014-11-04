#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mugg {
    namespace gui {
        class Sprite;
        class GUIManager;
    
        class SpriteBatch {
            private:
                GLuint  modelMatrixBufferID, texID, vaoID;
                unsigned int maxSprites, spriteCount;
                int stride, bufferSize;
                GLint modelMatrixLocation;
            
                mugg::gui::GUIManager* parent;
            public:
                SpriteBatch(mugg::gui::GUIManager*, unsigned int, GLuint, GLint);
                ~SpriteBatch();

                virtual void AddSprite(mugg::gui::Sprite*);
                virtual void UpdateSprite(mugg::gui::Sprite*);
        
                virtual int GetBufferSize();
                virtual int GetStride();

                virtual unsigned int GetSpriteCount();
                virtual unsigned int GetMaxSprites();
                
                virtual GLuint GetModelMatrixBufferID();
                virtual void SetModelMatrixBufferID(GLuint);

                virtual GLuint GetTextureID();
                virtual void SetTextureID(GLuint);

                virtual void Render();
        };
    }
}

#endif
