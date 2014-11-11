#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "scene/scenenode.hpp"
#include "graphics/shaderprogram.hpp"
#include "graphics/graphicsdefs.hpp"

#include "core/logger.hpp"

namespace mugg {
    namespace core {
        class Engine;
    }
    
    namespace scene {
        class SceneManager {
            private:
                std::vector<mugg::scene::SceneNode*> sceneNodes;
            
                std::string vertexShaderSrc = GLSL(
                    in vec3 v_position;
                    in vec2 v_uv;
                    in vec3 v_normal;

                    out vec2 f_uv;
                    out vec3 f_normal;

                    uniform mat4 u_model;
                    uniform mat4 u_projection;

                    void main(void) {
                        f_uv = v_uv;
                        f_normal = v_normal;
                        gl_Position = u_model * u_projection * vec4(v_position, 1.0);
                    }
                );

                std::string fragmentShaderSrc = GLSL(
                    in vec2 f_uv;
                    in vec3 f_normal;

                    out vec4 out_color;

                    uniform sampler2D sampler;

                    void main(void) {
                        out_color = texture(sampler, f_uv) * vec4(f_normal, 1.0); 
                    }
                );

                mugg::core::Engine* parent;
                mugg::graphics::Shader* vertexShader;
                mugg::graphics::Shader* fragmentShader;
                mugg::graphics::ShaderProgram* shaderProgram;
                
                std::string posAttribName, uvAttribName, normalAttribName;
                
                GLint posLocation, uvLocation, normalLocation;
            public:
                SceneManager(mugg::core::Engine*);
                ~SceneManager();

                bool Initialize();

                mugg::scene::SceneNode* CreateSceneNode();
                std::size_t GetNumberOfSceneNodes();
                bool GetSceneNodeByIndex(int, mugg::scene::SceneNode*&);

                void SetShaderProgram(mugg::graphics::ShaderProgram*);
                GLuint GetShaderProgramID();

                void Render();
        };
    }
}

#endif
