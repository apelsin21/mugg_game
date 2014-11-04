#include "graphics/mesh.hpp"

mugg::graphics::Mesh::Mesh(mugg::core::ContentManager* parent) {
    this->parent = parent;

    this->loaded = false;

    this->vaoID = -1;
    this->positionBufferID = -1;
    this->uvBufferID = -1;
    this->normalBufferID = -1;
    this->elementBufferID = -1;
    
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

mugg::graphics::Texture2D* mugg::graphics::Mesh::GetTexture() {
    return this->texture;
}
void mugg::graphics::Mesh::SetTexture(mugg::graphics::Texture2D* texture) {
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

    this->indices.clear();
    this->vertices.clear();
    this->normals.clear();
    this->uvs.clear();

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
               //mesh->SetTexture(this->CreateTexture2D(tempPath, false));
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

    this->loaded = true;
	this->filepath = filepath;
    return true;
}

std::string mugg::graphics::Mesh::GetFilepath() {
    return this->filepath;
}
void mugg::graphics::Mesh::SetFilepath(const std::string& filepath) {
    this->filepath = filepath;
}

void mugg::graphics::Mesh::SetIndices(const std::vector<unsigned short>& indices) {
    this->indices = indices;
}
std::vector<unsigned short> mugg::graphics::Mesh::GetIndices() {
    return this->indices;
}
int mugg::graphics::Mesh::GetIndexCount() {
    return this->indices.size();
}

void mugg::graphics::Mesh::SetVertices(const std::vector<glm::vec3>& vertices) {
    this->vertices = vertices;
}
std::vector<glm::vec3> mugg::graphics::Mesh::GetVertices() {
    return this->vertices;
}
int mugg::graphics::Mesh::GetVertexCount() {
    return this->vertices.size();
}

void mugg::graphics::Mesh::SetUVS(const std::vector<glm::vec2>& uvs) {
    this->uvs = uvs;
}
std::vector<glm::vec2> mugg::graphics::Mesh::GetUVS() {
    return this->uvs;
}
int mugg::graphics::Mesh::GetUVCount() {
    return this->uvs.size();
}

void mugg::graphics::Mesh::SetNormals(const std::vector<glm::vec3>& normals) {
    this->normals = normals;
}
std::vector<glm::vec3> mugg::graphics::Mesh::GetNormals() {
    return this->normals;
}
int mugg::graphics::Mesh::GetNormalCount() {
    return this->normals.size();
}
