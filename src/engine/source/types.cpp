#include "../include/types.h"
#include <GL/gl.h>

/*void TEXT_UI::load(const char* text, const char* fontPath, int fontSize, Color4 c, Vector2 pos, Uint32 warp, GLuint (*lod_txt_text)(const char *text, const char *fontPath, int fontSize, Color4 c, GLuint& textTexture, int& w, int& h, Uint32 warp, GLenum FILTER)) {
    this->position = pos;
    int w, h;

    this->texture = lod_txt_text(text, fontPath, fontSize, c, this->texture, w, h, warp, GL_LINEAR);

    this->size.x = w;
    this->size.y = h;
}*/

TEXT_UI::~TEXT_UI() {
    glDeleteTextures(1, &this->texture);
}



Vector2 parse_iv2(iVector2 iv2) {
    return Vector2(iv2.x, iv2.y);
}
