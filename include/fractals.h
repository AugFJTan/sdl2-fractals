#ifndef IDEAS_FRACTALS_H_
#define IDEAS_FRACTALS_H_

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void sierpinski_triangle(SDL_Renderer* renderer);
void sierpinski_carpet(SDL_Renderer* renderer);
void fractal_tree(SDL_Renderer* renderer);

#endif
