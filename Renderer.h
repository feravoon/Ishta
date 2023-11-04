#pragma once
#include "Camera.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_timer.h"

class Renderer
{
    public:
        SDL_Window* win;
        SDL_Renderer* rend;
        uint8_t* imByteArray;
        SDL_Texture* tex;
        SDL_Rect dest;
        float scale;
        Renderer(float scale, int resx, int resy);
        void render(uint8_t *image, int resx, int resy);
};