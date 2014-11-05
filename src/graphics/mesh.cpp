#include "graphics/mesh.hpp"

mugg::graphics::Mesh::Mesh(mugg::core::ContentManager* parent) {
    this->parent = parent;

    this->loaded = false;

    this->vaoID = -1;
    this->positionBufferID = -1;
    this->uvBufferID = -1;
    this->normalBufferID = -1;
    this->elementBufferID = -1;
   
    this->vertexCount = 0;
    this->indexCount = 0;
    this->normalCount = 0;
    this->uvCount = 0;

    this->texture = nullptr;
}
mugg::graphics::Mesh::~Mesh() {
	if(glIsVertexArray(this->vaoID)) {
		glDeleteVertexArrays(1, &vaoID);
	}
    if(glIsBuffer(positionBufferID) == GL_TRUE) {
		glDeleteBuffers(1, &positionBufferID);
	}
    if(glIsBuffer(uvBufferID) == GL_TRUE) {
		glDeleteBuffers(1, &uvBufferID);
	}
    if(glIsBuffer(normalBufferID) == GL_TRUE) {
        glDeleteBuffers(1, &normalBufferID);
	}
    if(glIsBuffer(elementBufferID) == GL_TRUE) {
		glDeleteBuffers(1, &this->elementBufferID);
	}
	
	if(this->texture != nullptr) {
		delete this->texture;
	}
}

mugg::graphics::Texture* mugg::graphics::Mesh::GetTexture() {
    return this->texture;
}
void mugg::graphics::Mesh::SetTexture(mugg::graphics::Texture* texture) {
    this->texture = texture;
}

GLuint mugg::graphics::Mesh::GetVAOID() {
    return this->vaoID;
}
void mugg::graphics::Mesh::SetVAOID(GLuint vaoID) {
    this->vaoID = vaoID;
}

GLuint mugg::graphics::Mesh::GetPositionBufferID() {
    return this->positionBufferID;
}
void mugg::graphics::Mesh::SetPositionBufferID(GLuint positionBufferID) {
    this->positionBufferID = positionBufferID;
}

GLuint mugg::graphics::Mesh::GetUVBufferID() {
    return this->uvBufferID;
}
void mugg::graphics::Mesh::SetUVBufferID(GLuint uvBufferID) {
    this->uvBufferID = uvBufferID;
}

GLuint mugg::graphics::Mesh::GetNormalBufferID() {
    return this->normalBufferID;
}
void mugg::graphics::Mesh::SetNormalBufferID(GLuint normalBufferID) {
    this->normalBufferID = normalBufferID;
}

GLuint mugg::graphics::Mesh::GetElementBufferID() {
    return this->elementBufferID;
}
void mugg::graphics::Mesh::SetElementBufferID(GLuint elementBufferID) {
    this->elementBufferID = elementBufferID;
}

bool mugg::graphics::Mesh::Load(const std::string& filepath) {
	if(filepath == "") {
        mugg::core::Log(mugg::core::LogLevel::Error, "Mesh tried to load empty filepath");
        return false;
    }
    
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(filepath.c_str(),
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);

    if(!scene) {
        mugg::core::Log(mugg::core::LogLevel::Error, "Mesh " + filepath + " failed to load, error:");
        mugg::core::Log(mugg::core::LogLevel::Error, importer.GetErrorString());
        return false;
    }

    std::vector<unsigned int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    if(scene->HasMeshes()) {
        for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
            const aiMesh* tempMesh = scene->mMeshes[i];

            //Check for vertices
            if(tempMesh->HasPositions()) {
                for(unsigned int u = 0; u < tempMesh->mNumVertices; u++) {
                    aiVector3D pos = tempMesh->mVertices[i];
                    vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
                }
                
				//If if has vertices, it has indices
                //Which is pretty catchy too
                for(unsigned int u = 0; u < tempMesh->mNumFaces; u++) {
                    if(tempMesh->mFaces[i].mNumIndices == 3) {
                        indices.push_back(tempMesh->mFaces[i].mIndices[0]);
                        indices.push_back(tempMesh->mFaces[i].mIndices[1]);
                        indices.push_back(tempMesh->mFaces[i].mIndices[2]);
                    }
                }
            }

			//Check for texture coordinates
            for(unsigned int u = 0; u < tempMesh->mNumVertices; u++) {
                for(unsigned int y = 0; y <= AI_MAX_NUMBER_OF_TEXTURECOORDS; y++) {
                    if(tempMesh->HasTextureCoords(y)) {
                        aiVector3D UVW = tempMesh->mTextureCoords[0][y];
                        uvs.push_back(glm::vec2(UVW.x, UVW.y));
                    }
                }
            }
              
            //Check for normals
            if(tempMesh->HasNormals()) {
                for(unsigned int u = 0; u < tempMesh->mNumVertices; u++) {
                    aiVector3D n = tempMesh->mNormals[u];
                    normals.push_back(glm::vec3(n.x, n.y, n.z));
                }
            }
        }
    } else {
        mugg::core::Log(mugg::core::LogLevel::Warning, "File " + filepath + " has no mesh(es).");
    }

    if(scene->mNumMaterials > 0) {
        const aiMaterial* material = scene->mMaterials[0];
        
       if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
           aiString path;

           if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
               //Make a full path
               std::string tempPath = filepath.substr(0, filepath.find_last_of("\\/"));
               tempPath += "/";
               tempPath += path.data;
               mugg::core::Log(mugg::core::LogLevel::Error, "Couldn't load texture " + tempPath + ", fix urgently!");
               //mesh->SetTexture(this->CreateTexture(tempPath, false));
           }
       }
    } else {
        mugg::core::Log(mugg::core::LogLevel::Info, "Mesh " + filepath + " has no textures");
    }

    if(glIsVertexArray(this->vaoID) != GL_TRUE) {
        glGenVertexArrays(1, &this->vaoID);
    }
    glBindVertexArray(this->vaoID);

    if(!vertices.empty()) {
        if(glIsBuffer(this->positionBufferID) != GL_TRUE) {
            glGenBuffers(1, &this->positionBufferID);
        }
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    }

    if(!uvs.empty()) {
        if(glIsBuffer(this->uvBufferID) != GL_TRUE) {
            glGenBuffers(1, &this->uvBufferID);
        }
        glBindBuffer(GL_ARRAY_BUFFER, this->uvBufferID);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    }

    if(!normals.empty()) {
        if(glIsBuffer(this->normalBufferID) != GL_TRUE) {
            glGenBuffers(1, &this->normalBufferID);
        }
        glBindBuffer(GL_ARRAY_BUFFER, this->normalBufferID);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    }

    if(!indices.empty()) {
        if(glIsBuffer(this->elementBufferID) != GL_TRUE) {
            glGenBuffers(1, &this->elementBufferID);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
    }
    
    this->vertexCount = vertices.size();
    this->indexCount = indices.size();
    this->normalCount = normals.size();
    this->uvCount = uvs.size();

    this->loaded = true;
	this->filepath = filepath;
    return true;
}

std::string mugg::graphics::Mesh::GetFilepath() {
    return this->filepath;
}

unsigned int mugg::graphics::Mesh::GetIndexCount() {
    return this->indexCount;
}
unsigned int mugg::graphics::Mesh::GetVertexCount() {
    return this->vertexCount;
}
unsigned int mugg::graphics::Mesh::GetUVCount() {
    return this->uvCount;
}
unsigned int mugg::graphics::Mesh::GetNormalCount() {
    return this->normalCount;
}
