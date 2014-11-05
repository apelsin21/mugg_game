#include "graphics/texture.hpp"

mugg::graphics::Texture::Texture(mugg::core::ContentManager* creator) : GLObject(creator) {
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

void mugg::graphics::Texture::SetFilepath(std::string filepath) {
    this->filepath = filepath;
}
std::string mugg::graphics::Texture::GetFilepath() {
    return this->filepath;
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
