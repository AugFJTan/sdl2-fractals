#include "fractals.h"
#include <cstdlib>
#include <ctime>

SDL_FPoint transform_to_plot(SDL_FRect plot, SDL_FPoint p);

void barnsley_fern(SDL_Renderer* renderer) {
	int max_iterations = 3000;
	float plot_length = 420.0;

	srand(time(NULL));

	SDL_FRect plot;
	plot.x = (SCREEN_WIDTH - plot_length) / 2.0;
	plot.y = (SCREEN_HEIGHT - plot_length) / 2.0;
	plot.w = plot_length;
	plot.h = plot_length;

	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);

	float x = 0.0;
	float y = 0.0;
	int t = 0;
	float xn = 0.0;
	float yn = 0.0;

	while (t < max_iterations) {
		int r = rand() % 101;  // Random number between 0 and 100

		if (r < 1) {
			xn = 0.0;
			yn = 0.16 * y;
		} else if (r < 86) {
			xn = 0.85 * x + 0.04 * y;
			yn = -0.04 * x + 0.85 * y + 1.6;
		} else if (r < 93) {
			xn = 0.2 * x - 0.26 * y;
			yn = 0.23 * x + 0.22 * y + 1.6;
		} else {
			xn = -0.15 * x + 0.28 * y;
			yn = 0.26 * x + 0.24 * y + 0.44;
		}

		SDL_FPoint p = transform_to_plot(plot, {xn, yn});
		SDL_RenderDrawPointF(renderer, p.x, p.y);

		x = xn;
		y = yn;

		t++;
	}
}

/*
	Plot range:
	-2.2 <= x <=  2.7
	 0.0 <= y <= 10.0
*/
SDL_FPoint transform_to_plot(SDL_FRect plot, SDL_FPoint p) {
	float scale = plot.h / 10.0;
	SDL_FPoint q;
	q.x = plot.x + plot.w / 2 + (p.x - 0.25) * scale;
	q.y = plot.y + plot.h - p.y * scale;
	return q;
}
