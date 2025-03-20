#include "../include/graphic.h"
#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

bool GRAPHICS::create(SDL_Window *window, Vector2 size) {
    this->window = window;
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context" << SDL_GetError() << "\n";
        return 0;
    }

    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1);

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, size.x, size.y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return 1;
}

void GRAPHICS::delete_context() {
    this->window = nullptr;
    SDL_GL_DeleteContext(context);
}

void GRAPHICS::draw_glTexture(GLuint texture, Vector2 position, Vector2 size) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(position.x,          position.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(position.x + size.x, position.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(position.x + size.x, position.y + size.y);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(position.x,          position.y + size.y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GRAPHICS::draw_glText(GLuint textTexture, Vector2 position, Vector2 size) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textTexture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(position.x,          position.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(position.x + size.x, position.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(position.x + size.x, position.y + size.y);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(position.x,          position.y + size.y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void GRAPHICS::draw_textUI(TEXT_UI text) {
    std::cout << "draw; " << text.texture << "\n";

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, text.texture);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(text.position.x,          text.position.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(text.position.x + text.size.x, text.position.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(text.position.x + text.size.x, text.position.y + text.size.y);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(text.position.x,          text.position.y + text.size.y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void GRAPHICS::clear_window(Color4 c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GRAPHICS::swap_buffers() {
    SDL_GL_SwapWindow(window);
}

GLuint GRAPHICS::load_text_texture(const char *text, const char *fontPath, int fontSize, Color4 c, GLuint& textTexture, int& w, int& h, Uint32 warp, GLenum FILTER) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << fontPath << "\n";
        return 0;
    }

    c.r *= 255;
    c.g *= 255;
    c.b *= 255;
    c.a *= 255;

    SDL_Color color = {static_cast<Uint8>(c.r), static_cast<Uint8>(c.g), static_cast<Uint8>(c.b), static_cast<Uint8>(c.a)};
    //SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Surface* surface;

    if (warp != -1) surface = TTF_RenderText_Blended_Wrapped(font, text, color, warp);
    else surface = TTF_RenderText_Blended(font, text, color);

    if (!surface) {
        std::cerr << "Failed to render text: " << text << "\n";
        TTF_CloseFont(font);
        return 0;
    }

    SDL_Surface* optimizedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    if (!optimizedSurface) {
        std::cerr << "Failed to optimize surface\n";
        TTF_CloseFont(font);
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, optimizedSurface->w, optimizedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, optimizedSurface->pixels);
    SDL_FreeSurface(optimizedSurface);
    TTF_CloseFont(font);
    w = surface->w;
    h = surface->h;
    textTexture = texture;
    return texture;
}

void GRAPHICS::delete_text_texture(GLuint id) {
    glDeleteTextures(1, &id);
}

GLuint GRAPHICS::load_image(const char* path, int filter, GLuint& source) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cerr << "Failed to load image: " << path << "\n";
        return 0;
    }

    SDL_Surface* optimizedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    if (!optimizedSurface) {
        std::cerr << "Failed to convert image: " << path << "\n";
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, optimizedSurface->w, optimizedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, optimizedSurface->pixels);

    source = texture;
    SDL_FreeSurface(optimizedSurface);
    return texture;
}

void GRAPHICS::delete_image(GLuint id) {
    glDeleteTextures(1, &id);
}
