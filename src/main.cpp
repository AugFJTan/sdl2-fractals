#include "fractals.h"
#include <stdio.h>

void (*fractal_arr[])(SDL_Renderer*) = {
	sierpinski_triangle,
	sierpinski_carpet,
	sierpinski_curve,
	fractal_tree,
	koch_snowflake,
	mandelbrot_set,
	box_factal,
	dragon_curve,
};

void show_fractal(SDL_Renderer* renderer, int fractal_idx) {
	SDL_SetRenderDrawColor(renderer, 0x7f, 0x7f, 0x7f, 0xff);  // Background
	SDL_RenderClear(renderer);
	fractal_arr[fractal_idx](renderer);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
				"SDL2 Fractals",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
		return 1;
	}

	int num_fractals = sizeof(fractal_arr) / sizeof(*fractal_arr);
	int fractal_idx = 0;

	show_fractal(renderer, fractal_idx);

	bool quit = false;
	bool update = false;
	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					update = true;
					break;
				default:
					break;
			}
		}

		if (update) {
			fractal_idx++;

			if (fractal_idx >= num_fractals)
				fractal_idx = 0;

			show_fractal(renderer, fractal_idx);

			update = false;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
