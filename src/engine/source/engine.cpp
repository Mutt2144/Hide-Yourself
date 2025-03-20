#include "../include/engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>

bool WINDOW::create(const char *title, Vector2 size) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        return 0;
    }

    return 1;
}

SDL_Window* WINDOW::get_window() {
    return window;
}

void WINDOW::quit() {
    SDL_DestroyWindow(window);
}

bool ENGINE::init(const char *title, Vector2 size) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return 0;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << "\n";
        return 0;
    }

    if (TTF_Init() < 0) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << "\n";
        return 0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

    if (!Window.create(title, size)
    || !Graphics.create(Window.get_window(), size)) return 0;

    running = 1;
    return 1;
}

void ENGINE::quit() {
    Graphics.delete_context();
    Window.quit();
    IMG_Quit();
    SDL_Quit();
}

void ENGINE::handle_events(SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_UP)        keys[K_UP]        = 1;
        if (e.key.keysym.sym == SDLK_DOWN)      keys[K_DOWN]      = 1;
        if (e.key.keysym.sym == SDLK_LEFT)      keys[K_LEFT]      = 1;
        if (e.key.keysym.sym == SDLK_RIGHT)     keys[K_RIGHT]     = 1;
        if (e.key.keysym.sym == SDLK_KP_ENTER)  keys[K_ENTER]     = 1;
        if (e.key.keysym.sym == SDLK_BACKSPACE) keys[K_BACKSPACE] = 1;
        if (e.key.keysym.sym == SDLK_ESCAPE)    keys[K_ESCAPE]    = 1;
    }

    if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_UP)        keys[K_UP]        = 0;
        if (e.key.keysym.sym == SDLK_DOWN)      keys[K_DOWN]      = 0;
        if (e.key.keysym.sym == SDLK_LEFT)      keys[K_LEFT]      = 0;
        if (e.key.keysym.sym == SDLK_RIGHT)     keys[K_RIGHT]     = 0;
        if (e.key.keysym.sym == SDLK_KP_ENTER)  keys[K_ENTER]     = 0;
        if (e.key.keysym.sym == SDLK_BACKSPACE) keys[K_BACKSPACE] = 0;
        if (e.key.keysym.sym == SDLK_ESCAPE)    keys[K_ESCAPE]    = 0;
    }
}

SDL_Event ENGINE::poll_events() {
    SDL_Event event;
    SDL_PollEvent(&event);

    handle_events(event);

    return event;
}
