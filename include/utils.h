#ifndef SDL2_FRACTALS_UTILS_H_
#define SDL2_FRACTALS_UTILS_H_

#include <SDL2/SDL.h>

SDL_FPoint midpoint(SDL_FPoint v1, SDL_FPoint v2);
SDL_FPoint transform(SDL_FPoint v, double mat_rot[2][2], SDL_FPoint v_trans);
SDL_FPoint centroid(SDL_FPoint v1, SDL_FPoint v2, SDL_FPoint v3);

#endif
