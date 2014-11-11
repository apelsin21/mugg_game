#include "graphics/shaderprogram.hpp"

mugg::graphics::ShaderProgram::ShaderProgram(bool createID = true) : GLObject() {
    this->linked = false;
    this->compiledSuccessfully = false;

    if(createID)
        this->CreateID();
}
mugg::graphics::ShaderProgram::~ShaderProgram() {
}

void mugg::graphics::ShaderProgram::CreateID() {
    this->ID = glCreateProgram();
    this->hasGeneratedID = true;
}
void mugg::graphics::ShaderProgram::DeleteID() {
    if(glIsProgram(this->ID) == GL_TRUE) {
        for(unsigned int i = 0; i < this->shaders.size(); i++) {
            glDetachShader(this->ID, this->shaders[i]);
        }
        
        this->hasGeneratedID = false;
        glDeleteProgram(this->ID);
    } else {
        std::cout << "Tried to delete invalid shaderprogram: " << this->ID << std::endl;
    }
}

bool mugg::graphics::ShaderProgram::AttachShader(mugg::graphics::Shader* shader) {
    if(glIsShader(shader->GetID()) == GL_FALSE) {
        std::cout << "Tried adding an unvalid shader to shaderprogram!\n";
        return false;
    }

    glAttachShader(this->ID, shader->GetID());

    this->shaders.push_back(shader->GetID());

    return true;
}

bool mugg::graphics::ShaderProgram::Link() {
    if(this->GetAttachedShaderCount() <= 0) {
        std::cout << "Tried to link shaderprogram without attaching any shaders!\n";
        return false;
    }

    glLinkProgram(this->ID);
    this->CheckForErrors();

    for(unsigned int i = 0; i < this->shaders.size(); i++) {
        glDetachShader(this->ID, this->shaders[i]);
    }

    if(!this->compiledSuccessfully) {
        this->linked = false;
        std::cout << this->GetLog() << std::endl;
        return false;
    }

    this->compiledSuccessfully = true;
    this->linked = true;

    return true;
}

void mugg::graphics::ShaderProgram::CheckForErrors() {
    GLint result = GL_FALSE;

    glGetProgramiv(this->ID, GL_LINK_STATUS, &result);

    if(result == GL_FALSE) {
        this->compiledSuccessfully = false;
    }

    this->compiledSuccessfully = true;
}

const char* mugg::graphics::ShaderProgram::GetLog() {
    int logLength = 0;
    glGetProgramiv(this->ID, GL_INFO_LOG_LENGTH, &logLength);
    
    GLchar buffer[logLength];
    glGetProgramInfoLog(this->ID, logLength, NULL, buffer);

    std::string returnval;

    for(unsigned int i = 0; i <= logLength; i++) {
        returnval += buffer[i];
    }

    return returnval.c_str();
}

bool mugg::graphics::ShaderProgram::Validate() {
    if(glIsProgram(this->ID) != GL_TRUE) {
        return false;
    }
    
    int result = GL_FALSE;

    glValidateProgram(this->ID);

    glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &result);

    if(result == GL_FALSE) {
        std::cout << "Validation log: " << this->GetLog() << std::endl;

        return false;
    }

    return true;
}

bool mugg::graphics::ShaderProgram::GetCompiledSuccessfully() {
    return this->compiledSuccessfully;
}

int mugg::graphics::ShaderProgram::GetAttrib(const std::string& name) {
    GLint attribLocation = -1;
    
    if(glIsProgram(this->ID) == GL_TRUE) {
        attribLocation = glGetAttribLocation(this->ID, name.c_str());
    } else {
        std::cout << "ERR: Tried to get attribute location from invalid shaderprogram!\n";
    }
    
    //Check for invalid location
    if(attribLocation < 0) {
        std::cout << "ERR: Got invalid attribute for name: " << name << " in shaderprogram " << this->ID << std::endl;
    }

    return attribLocation;
}
int mugg::graphics::ShaderProgram::GetUniform(const std::string& name) {
    GLint uniformLocation = -1;
    
    if(glIsProgram(this->ID) == GL_TRUE) {
        uniformLocation = glGetUniformLocation(this->ID, name.c_str());
    } else {
        std::cout << "ERR: Tried to get uniform location from invalid shaderprogram!\n";
    }

    //Check for invalid location
    if(uniformLocation < 0) {
        std::cout << "ERR: Got invalid uniform for name: " << name << " in shaderprogram " << this->ID << std::endl;
    }

    return uniformLocation;
}
void mugg::graphics::ShaderProgram::BindAttrib(GLuint index, const std::string& name) {
    if(glIsProgram(this->ID) == GL_TRUE) {
        glBindAttribLocation(this->ID, index, name.c_str());
    } else {
        std::cout << "ERR: Tried to bind attribute location in invalid shaderprogram!\n";
    }
}

int mugg::graphics::ShaderProgram::GetAttachedShaderCount() {
    GLint numberOfShaders = 0;

    glGetProgramiv(this->ID, GL_ATTACHED_SHADERS, &numberOfShaders);

    return numberOfShaders;
}
int mugg::graphics::ShaderProgram::GetActiveAttribCount() {
    GLint activeAttribs = 0;

    glGetProgramiv(this->ID, GL_ACTIVE_ATTRIBUTES, &activeAttribs);

    return activeAttribs;
}

void mugg::graphics::ShaderProgram::Use() {
    if(glIsProgram(this->ID)) {
        glUseProgram(this->ID);
    }
}
