#include "core/contentmanager.hpp"

mugg::core::ContentManager::ContentManager(mugg::core::Engine* parent) {
    this->parent = parent;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &this->maxTextureSize);
}
mugg::core::ContentManager::~ContentManager() {
    if(!this->textures.empty()) {
        for(unsigned int i = 0; i < this->textures.size(); i++) {
            this->DeleteTextureID(this->textures[i]->GetID());

            if(this->textures[i] != nullptr) {
                delete this->textures[i];
            }
        }
    }

    if(!this->shaders.empty()) {
        for(unsigned int i= 0; i < this->shaders.size(); i++) {
            this->DeleteShaderID(this->shaders[i]->GetID());
        
            if(this->shaders[i] != nullptr) {
                delete this->shaders[i];
            }
        }
    }

    if(!this->shaderPrograms.empty()) {
        for(unsigned int i = 0; i < this->shaders.size(); i++) {
            this->DeleteShaderProgramID(this->shaderPrograms[i]->GetID());
            
            if(this->shaderPrograms[i] != nullptr) {
                delete this->shaderPrograms[i];
            }
        }
    }

    if(!this->meshes.empty()) {
        for(unsigned int i = 0; i < this->meshes.size(); i++) {
            GLuint vaoID = this->meshes[i]->GetVAOID();
            GLuint positionBuffer = this->meshes[i]->GetPositionBufferID();
            GLuint uvBuffer = this->meshes[i]->GetUVBufferID();
            GLuint normalBuffer = this->meshes[i]->GetNormalBufferID();
            GLuint elementBuffer = this->meshes[i]->GetElementBufferID();

            glDeleteVertexArrays(1, &vaoID);
            
            if(glIsBuffer(positionBuffer) == GL_TRUE)
                glDeleteBuffers(1, &positionBuffer);
            if(glIsBuffer(uvBuffer) == GL_TRUE)
                glDeleteBuffers(1, &uvBuffer);
            if(glIsBuffer(normalBuffer) == GL_TRUE)
                glDeleteBuffers(1, &normalBuffer);
            if(glIsBuffer(elementBuffer) == GL_TRUE)
                glDeleteBuffers(1, &elementBuffer);
            
            delete this->meshes[i];
        }

    }
}

int mugg::core::ContentManager::GetMaxTextureSize() {
    return this->maxTextureSize;
}

mugg::graphics::Texture2D* mugg::core::ContentManager::CreateTexture2D(const std::string &filepath, bool mipmaps) {
    if(filepath == "") {
        std::cout << "Tried to load texture from empty string!\n";
        return nullptr;
    }

    FREE_IMAGE_FORMAT format;
    FIBITMAP* bitmap = nullptr;

    mugg::graphics::Texture2D* texture = new mugg::graphics::Texture2D(this);
    texture->GenID();
    texture->Bind();

    format = FreeImage_GetFileType(filepath.c_str(), 0);

    if(format == FIF_UNKNOWN) {
        format = FreeImage_GetFIFFromFilename(filepath.c_str());
    }

    if(format == FIF_UNKNOWN) {
        std::cout << "Failed to read format of texture " << filepath << ", invalid image!\n";
        texture->SetLoaded(false);
        this->textures.push_back(texture);
        return texture;
    }

    if(FreeImage_FIFSupportsReading(format)) {
        bitmap = FreeImage_Load(format, filepath.c_str());
    } else {
        std::cout << "Texture " << filepath << " has a format unsupported by FreeImage!\n";
        texture->SetLoaded(false);
        this->textures.push_back(texture);
        return texture;
    }

    if(!bitmap) {
        std::cout << "Failed to load texture " << filepath << ", corrupt or invalid bitmap.\n";
        texture->SetLoaded(false);
        this->textures.push_back(texture);
        return texture;
    }

    if(FreeImage_GetWidth(bitmap) > this->maxTextureSize || FreeImage_GetHeight(bitmap) > this->maxTextureSize) {
        std::cout << "Failed to load texture " << filepath << ", too big! Max resolution: " << this->maxTextureSize << "x" << this->maxTextureSize << "\n";
    }

    if(FreeImage_GetBPP(bitmap) != 32) {
        //Neccessary because FreeImage_ConvertTo32Bits() gives back a copy
        FIBITMAP* temp = FreeImage_ConvertTo32Bits(bitmap);

        if(!bitmap) {
            std::cout << "FreeImage failed to convert texture " << filepath << " to 32 bit colour!\n";
            texture->SetLoaded(false);
            this->textures.push_back(texture);
            return texture;
        }
        
        FreeImage_Unload(bitmap);
        bitmap = temp;
    }

    texture->Bind();

    texture->SetWrap(texture->GetUWrap(), texture->GetVWrap());
    texture->SetFilter(texture->GetMinFilter(), texture->GetMagFilter());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));

    if(mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    texture->SetWidth(FreeImage_GetWidth(bitmap));
    texture->SetHeight(FreeImage_GetHeight(bitmap));
    texture->SetColorsUsed(FreeImage_GetColorsUsed(bitmap));
    texture->SetBPP(FreeImage_GetBPP(bitmap));
    texture->SetFilepath(filepath);
    texture->SetLoaded(true);
    texture->SetUsesMipMaps(mipmaps);

    FreeImage_Unload(bitmap);
    
    this->textures.push_back(texture);

    return texture;
}
void mugg::core::ContentManager::DeleteTextureID(GLuint id) {
    if(glIsTexture(id) == GL_TRUE) {
        glDeleteTextures(1, &id);
    }
} 

mugg::graphics::Shader* mugg::core::ContentManager::CreateShader(mugg::graphics::ShaderType type, const std::string& filepath) {
    if(filepath == "") {
        std::cout << "Tried loading shader from empty path!\n";
        return nullptr;
    }

    GLuint id = glCreateShader(mugg::graphics::ShaderTypeToGLEnum(type));
    
    mugg::graphics::Shader* shader = new mugg::graphics::Shader(this);
    shader->SetID(id);

    shader->SetType(type);
    shader->SetFilepath(filepath);

    std::string data;

    if(!this->GetTextFile(filepath, data)) {
        std::cout << "Failed to load shader data from " << filepath << std::endl;
        this->shaders.push_back(shader);
        return shader;
    }

    shader->SetData(data);
    
    if(!shader->Compile()) {
        std::cout << "Shader " << filepath << " failed to compile!\n";
        this->shaders.push_back(shader);
        return shader;
    }

    this->shaders.push_back(shader);

    return shader;
}
void mugg::core::ContentManager::DeleteShaderID(GLuint id) {
    if(glIsShader(id) == GL_TRUE) {
        glDeleteShader(id);
    }
}

bool mugg::core::ContentManager::GetTextFile(const std::string filepath, std::string &out_data) {
    std::string data;
    
    if(filepath == "") {
        std::cout << "Failed to load text file because of empty path!\n";
        return false;
    }

    this->inStream.open(filepath, std::ios::in);

    if(this->inStream.is_open()) {
        std::string line;

        while(std::getline(this->inStream, line)) {
            data += "\n" + line;
        }

        this->inStream.close();
    } else {
        std::cout << "Failed to open " << filepath << " for reading!\n";
        return false;
    }

    out_data = data;

    return true;
}

mugg::graphics::ShaderProgram* mugg::core::ContentManager::CreateShaderProgram() {
    GLuint id = glCreateProgram();

    mugg::graphics::ShaderProgram* program = new mugg::graphics::ShaderProgram(this);
    program->SetID(id);

    this->shaderPrograms.push_back(program);

    return program;
}
void mugg::core::ContentManager::DeleteShaderProgramID(GLuint id) {
    if(glIsProgram(id) == GL_TRUE) {
        glDeleteProgram(id);
    }
}

mugg::graphics::Mesh* mugg::core::ContentManager::CreateMesh(const std::string& filepath) {
    if(filepath == "") {
        std::cout << "Path supplied to ContentManager::CreateMesh was empty!\n";
        return nullptr;
    }
    
    mugg::graphics::Mesh* mesh = new mugg::graphics::Mesh(this);

    mesh->SetFilepath(filepath);

    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(mesh->GetFilepath().c_str(),
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);

    if(!scene) {
        std::cout << "Failed to read Mesh from " << filepath << ", Assimp error string:\n";
        std::cout << importer.GetErrorString() << std::endl;
        this->meshes.push_back(mesh);
        return mesh;
    }
    
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    if(scene->HasMeshes()) {
        for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
            const aiMesh* tempMesh = scene->mMeshes[i];

            
            if(tempMesh->HasPositions()) {
                for(unsigned int u = 0; u < tempMesh->mNumVertices; u++) {
                    aiVector3D pos = tempMesh->mVertices[i];
                    vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
                }
                

                for(unsigned int u = 0; u < tempMesh->mNumFaces; u++) {
                    if(tempMesh->mFaces[i].mNumIndices == 3) {
                        indices.push_back(tempMesh->mFaces[i].mIndices[0]);
                        indices.push_back(tempMesh->mFaces[i].mIndices[1]);
                        indices.push_back(tempMesh->mFaces[i].mIndices[2]);
                    }
                }

            }


            for(unsigned int u = 0; u < tempMesh->mNumVertices; u++) {
                for(unsigned int y = 0; y <= AI_MAX_NUMBER_OF_TEXTURECOORDS; y++) {
                    if(tempMesh->HasTextureCoords(y)) {
                        aiVector3D UVW = tempMesh->mTextureCoords[0][y];
                        uvs.push_back(glm::vec2(UVW.x, UVW.y));
                    }
                }
            }
                
            

            if(tempMesh->HasNormals()) {
                for(unsigned int u = 0; u < tempMesh->mNumVertices; u++) {
                    aiVector3D n = tempMesh->mNormals[u];
                    normals.push_back(glm::vec3(n.x, n.y, n.z));
                }
                
            }
        }
    }

    mesh->SetNormals(normals);
    mesh->SetUVS(uvs);
    mesh->SetIndices(indices);
    mesh->SetVertices(vertices);

    if(scene->mNumMaterials > 0) {
        const aiMaterial* material = scene->mMaterials[0];
        
       if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
           aiString path;

           if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
               std::string tempPath = filepath.substr(0, filepath.find_last_of("\\/"));
               tempPath += "/";
               tempPath += path.data;
               mesh->SetTexture(this->CreateTexture2D(tempPath, false));
           }
       }
    }

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    mesh->SetVAOID(vaoID);
    mesh->SetPositionBufferID(vertexbuffer);
    mesh->SetUVBufferID(uvbuffer);
    mesh->SetNormalBufferID(normalbuffer);
    mesh->SetElementBufferID(elementbuffer);

    this->meshes.push_back(mesh);
    return mesh;
}
