#include "fractals.h"

static SDL_FPoint to_julia_scale(SDL_FPoint p);

void julia_set(SDL_Renderer* renderer) {
	int max_iteration = 100;
	float R = 2.0;  // Escape radius
	float cx = -0.8;
	float cy = 0.156;

	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 0xff);

	for (int py = 0; py < SCREEN_HEIGHT; py++) {
		for (int px = 0; px < SCREEN_WIDTH; px++) {
			SDL_FPoint j = to_julia_scale({px, py});
			float zx = j.x;
			float zy = j.y;

			int iteration = 0;

			while(zx * zx + zy * zy < R * R && iteration < max_iteration) {
				float xtemp = zx * zx - zy * zy;
				zy = 2 * zx * zy + cy;
				zx = xtemp + cx;
				iteration++;
			}

			if (iteration == max_iteration)
				SDL_RenderDrawPoint(renderer, px, py);
		}
	}
}

static SDL_FPoint to_julia_scale(SDL_FPoint p) {
	SDL_FPoint j;
	j.x = -1.8 + p.x * 3.6 / SCREEN_WIDTH;
	j.y = -1.8 + (SCREEN_HEIGHT - p.y) * 3.6 / SCREEN_HEIGHT;
	return j;
}
