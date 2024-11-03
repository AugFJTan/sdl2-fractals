#include "fractals.h"
#include <cmath>
#include <vector>

static void segment(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, float theta, float delta);

void dragon_curve(SDL_Renderer* renderer) {
	int length = 180;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT / 2;

	SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);

	std::vector<SDL_FPoint> points;

	SDL_FPoint start = {x - length, y};
	SDL_FPoint end   = {x + length, y};

	// Adjust to centre of window
	float initial_length = magnitude(start, end);

	float x_offset = initial_length / 12;
	float y_offset = initial_length / 6;

	start.x += x_offset;
	start.y += y_offset;

	end.x += x_offset;
	end.y += y_offset;

	segment(0, points, start, end, 0, 45.0 * M_PI / 180.0);
	points.push_back(end);

	SDL_RenderDrawLinesF(renderer, points.data(), points.size());
}

static void segment(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, float theta, float delta) {
	if (iter == 12) {
		points.push_back(v1);
		return;
	}

	float length = magnitude(v1, v2);
	float new_length = length * (1 / sqrt(2));

	SDL_FPoint va;
	va.x = v1.x + new_length * cos(theta + delta);
	va.y = v1.y - new_length * sin(theta + delta);

	iter++;

	segment(iter, points, v1, va, theta + delta, 45.0 * M_PI / 180.0);
	segment(iter, points, va, v2, theta - delta, -45.0 * M_PI / 180.0);
}
