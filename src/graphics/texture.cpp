#include "graphics/texture.hpp"

mugg::graphics::Texture::Texture() : GLObject() {
    //Numbers
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
    this->ID = 0;
    this->colorsUsed = 0;
    this->index = 0;

    //Booleans
    this->loaded = false;
    this->mipMaps = false;
    this->hasGeneratedID = false;

    //Enums
    this->minFilter = mugg::graphics::TextureFilter::Nearest;
    this->magFilter = mugg::graphics::TextureFilter::Nearest;
    this->uWrap = mugg::graphics::TextureWrap::ClampToEdge;
    this->vWrap = mugg::graphics::TextureWrap::ClampToEdge;
}
mugg::graphics::Texture::~Texture() {
}

bool mugg::graphics::Texture::Load(const std::string& filepath, bool genMipMaps) {
    if(filepath == "") {
        mugg::core::Log(mugg::core::LogLevel::Error, "Tried to load texture from empty filepath");
        return false;
    }

    FREE_IMAGE_FORMAT format;
    FIBITMAP* bitmap = nullptr;

    this->GenID();
    this->Bind();

    //Try to get texture format
    format = FreeImage_GetFileType(filepath.c_str(), 0);

    if(format == FIF_UNKNOWN) {
        format = FreeImage_GetFIFFromFilename(filepath.c_str());
    
        if(format == FIF_UNKNOWN) {
            mugg::core::Log(mugg::core::LogLevel::Error, "Failed to load texture " + filepath + ", invalid format or corrupt/invalid texture");
            return false;
        }
    }

    if(FreeImage_FIFSupportsReading(format)) {
        bitmap = FreeImage_Load(format, filepath.c_str());
    } else {
        mugg::core::Log(mugg::core::LogLevel::Error, "Failed to load texture " + filepath + ", unsupported format for reading!");
        return false;
    }

    if(!bitmap) {
        mugg::core::Log(mugg::core::LogLevel::Error, "Failed to load texture " + filepath + ", corrupt or invalid bitmap!");
        return false;
    }

    if(FreeImage_GetBPP(bitmap) != 32) {
        //Neccessary because FreeImage_ConvertTo32Bits() gives back a copy for some reason
        FIBITMAP* temp = FreeImage_ConvertTo32Bits(bitmap);

        if(!temp) {
            mugg::core::Log(mugg::core::LogLevel::Error, "Failed to convert texture " + filepath + ", to 32 bits!");
            return false;
        }

        FreeImage_Unload(bitmap);
        bitmap = temp;
    }

    this->Bind();

    this->SetWrap(this->uWrap, this->vWrap);
    this->SetFilter(this->minFilter, this->magFilter);
    this->width     =   FreeImage_GetWidth(bitmap);
    this->height    =   FreeImage_GetHeight(bitmap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));

    if(genMipMaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    this->bpp       =   FreeImage_GetBPP(bitmap);
    this->filepath  =   filepath;
    this->loaded    =   true;
    this->mipMaps   =   genMipMaps;

    return true;
}

void mugg::graphics::Texture::SetFilepath(std::string filepath) {
    this->filepath = filepath;
}
std::string mugg::graphics::Texture::GetFilepath() {
    return this->filepath;
}

void mugg::graphics::Texture::SetWidth(int width) {
    this->width = width;
}
int mugg::graphics::Texture::GetWidth() {
    return this->width;
}

void mugg::graphics::Texture::SetHeight(int height) {
    this->height = height;
}
int mugg::graphics::Texture::GetHeight() {
    return this->height;
}

void mugg::graphics::Texture::SetBPP(int bpp) {
    this->bpp = bpp;
}
int mugg::graphics::Texture::GetBPP() {
    return this->bpp;
}

void mugg::graphics::Texture::SetColorsUsed(int colorsUsed) {
    this->colorsUsed = colorsUsed;
}
int mugg::graphics::Texture::GetColorsUsed() {
    return this->colorsUsed;
}

void mugg::graphics::Texture::SetLoaded(bool loaded) {
    this->loaded = loaded;
}
bool mugg::graphics::Texture::IsLoaded() {
    return this->loaded;
}

void mugg::graphics::Texture::SetUsesMipMaps(bool mipmaps) {
    this->mipMaps = mipmaps;
}
bool mugg::graphics::Texture::UsesMipMaps() {
    return this->mipMaps;
}

mugg::graphics::TextureWrap mugg::graphics::Texture::GetUWrap() {
    return this->uWrap;
}
mugg::graphics::TextureWrap mugg::graphics::Texture::GetVWrap() {
    return this->vWrap;
}
void mugg::graphics::Texture::SetWrap(TextureWrap u, TextureWrap v) {
    this->uWrap = u;
    this->vWrap = v;
    this->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGLEnum(u));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGLEnum(v));
}

void mugg::graphics::Texture::LoadDefault() {
    if(glIsTexture(this->ID) == GL_FALSE) {
        glGenTextures(1, &this->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, this->defaultTexture);
    
        this->SetFilter(TextureFilter::Nearest, TextureFilter::Nearest);            
        this->SetWrap(TextureWrap::Repeat, TextureWrap::Repeat);
    
        this->hasGeneratedID = true;
    }
}

mugg::graphics::TextureFilter mugg::graphics::Texture::GetMinFilter() {
    return this->minFilter;
}
mugg::graphics::TextureFilter mugg::graphics::Texture::GetMagFilter() {
    return this->magFilter;
}
void mugg::graphics::Texture::SetFilter(TextureFilter minFilter, TextureFilter magFilter) {
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGLEnum(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGLEnum(magFilter));
}

void mugg::graphics::Texture::GenID() {
    glGenTextures(1, &this->ID);
    this->hasGeneratedID = true;
}

void mugg::graphics::Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
void mugg::graphics::Texture::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
