#include "fractals.h"
#include <vector>

void sierpinski(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, SDL_FPoint v3);

void sierpinski_curve(SDL_Renderer* renderer) {
	int total_length = 420;

	float x = (SCREEN_WIDTH - total_length) / 2.0;
	float y = (SCREEN_HEIGHT - total_length) / 2.0;

	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);

	std::vector<SDL_FPoint> points;

	SDL_FPoint v1 = {x, y};
	SDL_FPoint v2 = {x + total_length, y};
	SDL_FPoint v3 = {x, y + total_length};
	SDL_FPoint v4 = {x + total_length, y + total_length};

	sierpinski(0, points, v2, v1, v4);
	sierpinski(0, points, v3, v4, v1);

	for (int i = 0; i < points.size(); i++) {
		if (i < points.size() - 1)
			SDL_RenderDrawLineF(renderer, points[i].x, points[i].y, points[i+1].x, points[i+1].y);
		else
			SDL_RenderDrawLineF(renderer, points[i].x, points[i].y, points[0].x, points[0].y);
	}
}

void sierpinski(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, SDL_FPoint v3) {
	if (iter == 9) {
		points.push_back(centroid(v1, v2, v3));
		return;
	}

	iter++;

	SDL_FPoint v4 = midpoint(v2, v3);

	sierpinski(iter, points, v4, v2, v1);
	sierpinski(iter, points, v4, v1, v3);
}
