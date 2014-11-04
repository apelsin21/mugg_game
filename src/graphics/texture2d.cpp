#include "graphics/texture2d.hpp"

mugg::graphics::Texture2D::Texture2D(mugg::core::ContentManager* creator) : GLObject(creator) {
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
mugg::graphics::Texture2D::~Texture2D() {
}

void mugg::graphics::Texture2D::SetWidth(int width) {
    this->width = width;
}
int mugg::graphics::Texture2D::GetWidth() {
    return this->width;
}

void mugg::graphics::Texture2D::SetHeight(int height) {
    this->height = height;
}
int mugg::graphics::Texture2D::GetHeight() {
    return this->height;
}

void mugg::graphics::Texture2D::SetBPP(int bpp) {
    this->bpp = bpp;
}
int mugg::graphics::Texture2D::GetBPP() {
    return this->bpp;
}

void mugg::graphics::Texture2D::SetColorsUsed(int colorsUsed) {
    this->colorsUsed = colorsUsed;
}
int mugg::graphics::Texture2D::GetColorsUsed() {
    return this->colorsUsed;
}

void mugg::graphics::Texture2D::SetFilepath(std::string filepath) {
    this->filepath = filepath;
}
std::string mugg::graphics::Texture2D::GetFilepath() {
    return this->filepath;
}

void mugg::graphics::Texture2D::SetLoaded(bool loaded) {
    this->loaded = loaded;
}
bool mugg::graphics::Texture2D::IsLoaded() {
    return this->loaded;
}

void mugg::graphics::Texture2D::SetUsesMipMaps(bool mipmaps) {
    this->mipMaps = mipmaps;
}
bool mugg::graphics::Texture2D::UsesMipMaps() {
    return this->mipMaps;
}

mugg::graphics::TextureWrap mugg::graphics::Texture2D::GetUWrap() {
    return this->uWrap;
}
mugg::graphics::TextureWrap mugg::graphics::Texture2D::GetVWrap() {
    return this->vWrap;
}
void mugg::graphics::Texture2D::SetWrap(TextureWrap u, TextureWrap v) {
    this->uWrap = u;
    this->vWrap = v;
    this->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGLEnum(u));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGLEnum(v));
}

void mugg::graphics::Texture2D::LoadDefault() {
    if(glIsTexture(this->ID) == GL_FALSE) {
        glGenTextures(1, &this->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, this->defaultTexture);
    
        this->SetFilter(TextureFilter::Nearest, TextureFilter::Nearest);            
        this->SetWrap(TextureWrap::Repeat, TextureWrap::Repeat);
    
        this->hasGeneratedID = true;
    }
}

mugg::graphics::TextureFilter mugg::graphics::Texture2D::GetMinFilter() {
    return this->minFilter;
}
mugg::graphics::TextureFilter mugg::graphics::Texture2D::GetMagFilter() {
    return this->magFilter;
}
void mugg::graphics::Texture2D::SetFilter(TextureFilter minFilter, TextureFilter magFilter) {
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToGLEnum(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToGLEnum(magFilter));
}

void mugg::graphics::Texture2D::GenID() {
    glGenTextures(1, &this->ID);
    this->hasGeneratedID = true;
}

void mugg::graphics::Texture2D::Bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
void mugg::graphics::Texture2D::UnBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
