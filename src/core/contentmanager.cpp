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
