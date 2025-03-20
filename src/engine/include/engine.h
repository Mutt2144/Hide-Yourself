#pragma once

#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_opengl.h>

#include "types.h"
#include "graphic.h"
#include "timer.h"

class WINDOW {
private:
    SDL_Window* window;

public:
    bool create(const char* title, Vector2 size);
    SDL_Window* get_window();
    void quit();
};

class ENGINE {
public:
    TIMER Timer;
    WINDOW Window;
    GRAPHICS Graphics;

    bool running;
    bool keys[16];

    bool init(const char* title, Vector2 size);
    void quit();

    void handle_events(SDL_Event& e);
    SDL_Event poll_events();
};
