#ifndef SDL2_FRACTALS_FRACTALS_H_
#define SDL2_FRACTALS_FRACTALS_H_

#include <SDL2/SDL.h>
#include "utils.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void sierpinski_triangle(SDL_Renderer* renderer);
void sierpinski_carpet(SDL_Renderer* renderer);
void sierpinski_curve(SDL_Renderer* renderer);
void fractal_tree_line(SDL_Renderer* renderer);
void fractal_tree_shape(SDL_Renderer* renderer);
void koch_snowflake_line(SDL_Renderer* renderer);
void koch_snowflake_shape(SDL_Renderer* renderer);
void mandelbrot_set(SDL_Renderer* renderer);
void box_factal(SDL_Renderer* renderer);
void dragon_curve(SDL_Renderer* renderer);
void barnsley_fern(SDL_Renderer* renderer);
void gosper_island(SDL_Renderer* renderer);

#endif
