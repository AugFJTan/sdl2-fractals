#include "fractals.h"

static SDL_FPoint to_mandelbrot_scale(SDL_FPoint p);

void mandelbrot_set(SDL_Renderer* renderer) {
	int max_iteration = 100;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

	for (int py = 0; py < SCREEN_HEIGHT; py++) {
		for (int px = 0; px < SCREEN_WIDTH; px++) {
			SDL_FPoint m = to_mandelbrot_scale({px, py});
			float x0 = m.x;
			float y0 = m.y;

			float x = 0;
			float y = 0;

			int iteration = 0;

			while (x*x + y*y <= 4 && iteration < max_iteration) {
				float xtemp = x*x - y*y + x0;
				y = 2*x*y + y0;
				x = xtemp;
				iteration++;
			}

			if (iteration == max_iteration)
				SDL_RenderDrawPoint(renderer, px, py);
		}
	}
}

static SDL_FPoint to_mandelbrot_scale(SDL_FPoint p) {
	SDL_FPoint m;
	m.x = -2.0 + p.x * 2.47 / SCREEN_WIDTH;
	m.y = -1.12 + p.y * 2.24 / SCREEN_HEIGHT;
	return m;
}
