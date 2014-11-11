#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/shaderprogram.hpp"
#include "graphics/shader.hpp"
#include "graphics/graphicsdefs.hpp"

#include "gui/spritebatch.hpp"

#include "core/fileutils.hpp"
#include "core/logger.hpp"

namespace mugg {
    namespace gui {
        class Sprite;
        
        class GUIManager {
            private:
                std::string vertexShaderSrc = GLSL(
                    in vec3 v_position;
                    in vec2 v_uv;
                    in mat4 v_model;

                    out vec2 f_uv;

                    uniform mat4 u_projection;

                    void main(void) {
                        f_uv = v_uv;
                        gl_Position = u_projection * v_model * vec4(v_position, 1.0);
                    }
                );
                
                std::string fragmentShaderSrc = GLSL(
                    in vec2 f_uv;

                    out vec4 out_color;

                    uniform sampler2D sampler;

                    void main(void) {
                        out_color = texture(sampler, f_uv);
                    }
                );

                std::vector<mugg::gui::Sprite*> sprites;
                std::vector<unsigned int> spritesToBeUpdated;
                std::vector<mugg::gui::SpriteBatch*> spriteBatches;
                    
                GLuint vaoID, positionBufferID, uvBufferID;
                
                mugg::graphics::Shader* vertexShader;
                mugg::graphics::Shader* fragmentShader;
                mugg::graphics::ShaderProgram* shaderProgram;
               
                std::string posAttribName, uvAttribName, modelAttribName, projectionMatrixUniformName;
                GLint posLocation, uvLocation, modelLocation, projectionMatrixUniformLocation;

                glm::mat4 projectionMatrix;

                void UpdateSpriteBatches();
            public:
                GUIManager();
                ~GUIManager();

                bool Initialize();

                mugg::gui::Sprite* CreateSprite();
                void UpdateSprite(unsigned int);
                std::size_t GetNumberOfSprites();
                bool GetSpriteByIndex(int, mugg::gui::Sprite*&);

                mugg::gui::SpriteBatch* CreateSpriteBatch();

                mugg::graphics::ShaderProgram* GetShaderProgram();
                void SetShaderProgram(mugg::graphics::ShaderProgram*);

                glm::mat4 GetProjectionMatrix();
                void SetProjectionMatrix(const glm::mat4&);

                void Render();
        };
    }
}

#endif
