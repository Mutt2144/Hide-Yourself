#pragma once

#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

#include "types.h"

class GRAPHICS {
private:
    SDL_Window* window;
    SDL_GLContext context;

public:
    bool create(SDL_Window* window, Vector2 size);
    void delete_context();

    // draw functions
    void draw_glTexture(GLuint texture, Vector2 position, Vector2 size);
    void draw_glText(GLuint textTexture, Vector2 position, Vector2 size);

    // moduled functions
    void draw_textUI(TEXT_UI text);

    void clear_window(Color4 c);
    void swap_buffers();

    static GLuint load_text_texture(const char* text, const char* fontPath, int fontSize, Color4 c, GLuint& textTexture, int& w, int& h, Uint32 warp, GLenum FILTER);
    void delete_text_texture(GLuint id);

    GLuint load_image(const char* path, int filter, GLuint& source);
    void delete_image(GLuint id);
};
