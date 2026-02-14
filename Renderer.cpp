#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

Renderer::Renderer(float scale, int resx, int resy)
{
	this->scale = scale;
	
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // creates a window
    this->win = SDL_CreateWindow("IshTa", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resx*this->scale, resy*this->scale, SDL_WINDOW_ALLOW_HIGHDPI);
 
    // triggers the program that controls your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
 
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); // bilinear

    // creates a renderer to render our images
    this->rend = SDL_CreateRenderer(win, -1, render_flags);

    SDL_ShowCursor(SDL_DISABLE);
}

void pixel_and(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32 * const target_pixel = (Uint32 *) ((Uint8 *)surface->pixels + y*surface->pitch + x*surface->format->BytesPerPixel);
	*target_pixel &= pixel;	
}

void black_to_transparent(SDL_Surface *surface, int x, int y)
{
	Uint32 * const target_pixel = (Uint32 *) ((Uint8 *)surface->pixels + y*surface->pitch + x*surface->format->BytesPerPixel);
	if (*target_pixel == 0xff000000)
		*target_pixel = 0x00000000;	
}

void Renderer::render(uint8_t *image, int resx, int resy)
{

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");


	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(image, resx, resy, 24, resx*3, SDL_PIXELFORMAT_RGB24);
	
	//SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(image, resx, resy, 24, resx*3, SDL_PIXELFORMAT_RGB888);

    this->tex = SDL_CreateTextureFromSurface(rend, surface);
    //SDL_SetTextureScaleMode(tex, SDL_ScaleModeBest);
    SDL_FreeSurface(surface);

    // set the background color
    SDL_SetRenderDrawColor(rend,0,0,0,SDL_ALPHA_OPAQUE);

    // clears the screen
    SDL_RenderClear(rend);

    // Game frame texture coordinates
    dest.w = resx*2*this->scale;
    dest.h = resy*2*this->scale;
    dest.x = 0*this->scale;
    dest.y = 0*this->scale;
    
	SDL_RenderCopy(rend,this->tex,NULL,&dest);

    SDL_DestroyTexture(this->tex);
    SDL_RenderPresent(rend);
}