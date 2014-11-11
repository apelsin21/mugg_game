#include "graphics/shader.hpp"

mugg::graphics::Shader::Shader(mugg::graphics::ShaderType type, bool createID) : GLObject() {
    this->type = type;
    this->loaded = false;
    this->compiledSuccessfully = false;

    if(createID)
        this->CreateID();
}
mugg::graphics::Shader::~Shader() {
}

void mugg::graphics::Shader::CreateID() {
    //this->ID = glCreateShader(mugg::graphics::ShaderTypeToGLEnum(this->type));
    this->ID = glCreateShader(GL_VERTEX_SHADER);
    this->hasGeneratedID = true;
}
void mugg::graphics::Shader::DeleteID() {
    if(glIsShader(this->ID) == GL_TRUE) {
        this->hasGeneratedID = false;
        glDeleteShader(this->ID);
    } else {
        std::cout << "Tried deleting invalid shader " << this->ID << std::endl;
    }
}

mugg::graphics::ShaderType mugg::graphics::Shader::GetType() {
    return this->type;
}
void mugg::graphics::Shader::SetType(mugg::graphics::ShaderType type) {
    this->type = type;
}

std::string mugg::graphics::Shader::GetFilepath() {
    return this->filepath;
}
void mugg::graphics::Shader::SetFilepath(std::string filepath) {
    this->filepath = filepath;
}

bool mugg::graphics::Shader::GetLoaded() {
    return this->loaded;
}

bool mugg::graphics::Shader::GetCompiledSuccessfully() {
    return this->compiledSuccessfully;
}

std::string mugg::graphics::Shader::GetData() {
    return this->data;
}
void mugg::graphics::Shader::SetData(const std::string& data) {
    this->loaded = true;
    this->data = data;
}

bool mugg::graphics::Shader::Load(const std::string& path) {
    if(path == "") {
        std::cout << "Got empty string as shader filepath!\n";
        return false;
    }

    if(!mugg::io::LoadTextFromFile(path, this->data)) {
        return false;
    }

    return true;
}

bool mugg::graphics::Shader::Compile() {
    if(!this->Validate()) {
        std::cout << "Tried to compile unvalid OpenGL shader!\n";
        this->compiledSuccessfully = false;
        return false;
    }

    const char* tempData = this->data.c_str();
    glShaderSource(this->ID, 1, &tempData, NULL);
    glCompileShader(this->ID);

    this->CheckForErrors();

    if(!this->compiledSuccessfully) {
        if(this->type == mugg::graphics::ShaderType::VertexShader) {
            std::cout << "Error in vertex shader:\n" << this->GetLog() << std::endl;
        } else if(this->type == mugg::graphics::ShaderType::FragmentShader) {
            std::cout << "Error in fragment shader:\n" << this->GetLog() << std::endl;
        }

        return false;
    }

    this->compiledSuccessfully = true;
    return true;
}

void mugg::graphics::Shader::CheckForErrors() {
    GLint result = GL_FALSE;
    glGetShaderiv(this->ID, GL_COMPILE_STATUS, &result);

    this->compiledSuccessfully = (bool)result;
}

const char* mugg::graphics::Shader::GetLog() {
    GLint logLength = 0;
    glGetShaderiv(this->ID, GL_INFO_LOG_LENGTH, &logLength);

    GLchar buffer[logLength];
    glGetShaderInfoLog(this->ID, logLength, NULL, buffer);
    
    std::string returnval;

    for(int i = 0; i <= logLength; i++) {
        returnval += buffer[i];
    }

    return returnval.c_str();
}

bool mugg::graphics::Shader::Validate() {
    GLboolean err = glIsShader(this->ID);

    if(err == GL_FALSE) {
        return false;
    }

    this->hasGeneratedID = err;

    return true;
}
