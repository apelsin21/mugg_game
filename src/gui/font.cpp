#include "gui/font.hpp"

mugg::gui::Font::Font(mugg::gui::GUIManager* parent) {
    this->parent = parent;

    this->width = 0;
    this->height = 0;
    this->pixelSize = 0;

    if(FT_Init_FreeType(&this->ft)) {
        std::cout << "ERR: Failed to initialize FreeType!\n";
    }
}
mugg::gui::Font::~Font() {
}

bool mugg::gui::Font::Load(const std::string& path, unsigned int pixelSize = 48) {
    if(FT_New_Face(this->ft, path.c_str(), 0, &this->face)) {
        std::cout << "ERR: Failed to load font " << path << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(this->face, 0, pixelSize);

    this->g = this->face->glyph;
    int w = 0;
    int h = 0;

    for(int i = 32; i < 128; i++) {
        if(FT_Load_Char(this->face, i, FT_LOAD_RENDER)) {
            std::cout << "ERR: Loading character " << i << " from " << path << " failed!\n";
        }

        w += this->g->bitmap.width;
        h = std::max(h, this->g->bitmap.rows);

        this->width = w;
    }

    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, w, h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, nullptr);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int x = 0;

    for(int i = 32; i < 128; i++) {
        if(FT_Load_Char(this->face, i, FT_LOAD_RENDER))
            continue;

        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, this->g->bitmap.width, this->g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, this->g->bitmap.buffer);

        x += this->g->bitmap.width;
        
        const uint8_t *p;

        this->c[*p].ax = this->g->advance.x >> 6;
        this->c[*p].ay = this->g->advance.y >> 6;
        
        this->c[*p].bw = this->g->bitmap.width;
        this->c[*p].bh = this->g->bitmap.rows;
        
        this->c[*p].bl = this->g->bitmap_left;
        this->c[*p].bt = this->g->bitmap_top;
        
        this->c[*p].tx = (float)x / w;
    }

}

GLuint mugg::gui::Font::GetTextureID() {
    return this->textureID;
}
void mugg::gui::Font::SetTextureID(GLuint id) {
    this->textureID = id;
}

unsigned int mugg::gui::Font::GetPixelSize() {
    return this->pixelSize;
}
int mugg::gui::Font::GetWidth() {
    return this->width;
}
int mugg::gui::Font::GetHeight() {
    return this->height;
}
