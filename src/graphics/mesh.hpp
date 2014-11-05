#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>
#include <iostream>
#include <string>

#include "graphics/texture.hpp"
#include "graphics/color.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/logger.hpp"

namespace mugg {
    namespace core {
        class ContentManager;
    }
    
    namespace graphics {
        class Mesh {
            private:
                mugg::graphics::Texture* texture;

                unsigned int indexCount;
                unsigned int vertexCount;
                unsigned int uvCount;
                unsigned int normalCount;

                std::string filepath;

                GLuint vaoID, positionBufferID, uvBufferID, normalBufferID, elementBufferID;

                bool loaded;

                mugg::core::ContentManager* parent;
            public:
                Mesh(mugg::core::ContentManager*);
                ~Mesh();

                mugg::graphics::Texture* GetTexture();
                void SetTexture(mugg::graphics::Texture*);

                unsigned int GetIndexCount();
                unsigned int GetVertexCount();
                unsigned int GetUVCount();
                unsigned int GetNormalCount();
                
                bool Load(const std::string&);

                GLuint GetVAOID();
                void SetVAOID(GLuint);
                
                GLuint GetPositionBufferID();
                void SetPositionBufferID(GLuint);
                
                GLuint GetUVBufferID();
                void SetUVBufferID(GLuint);
                
                GLuint GetNormalBufferID();
                void SetNormalBufferID(GLuint);
                
                GLuint GetElementBufferID();
                void SetElementBufferID(GLuint);
                
                std::string GetFilepath();
        };
    }
}

#endif
