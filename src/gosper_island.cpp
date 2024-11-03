#include "fractals.h"
#include <cmath>
#include <vector>

static void edge(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, float theta);

void gosper_island(SDL_Renderer* renderer) {
	float edge_length = 200.0;
	float half_height = edge_length * cos(30.0 * M_PI / 180.0);

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT / 2;

	SDL_FPoint v1 = {x - edge_length, y};
	SDL_FPoint v2 = {x - edge_length / 2, y - half_height};
	SDL_FPoint v3 = {x + edge_length / 2, y - half_height};
	SDL_FPoint v4 = {x + edge_length, y};
	SDL_FPoint v5 = {x + edge_length / 2, y + half_height};
	SDL_FPoint v6 = {x - edge_length / 2, y + half_height};

	SDL_FPoint base[7] = {v1, v2, v3, v4, v5, v6, v1};
	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
	SDL_RenderDrawLinesF(renderer, base, 7);

	std::vector<SDL_FPoint> points;

	edge(0, points, v1, v2, -60.0 * M_PI / 180.0);
	edge(0, points, v2, v3, 0.0);
	edge(0, points, v3, v4, 60.0 * M_PI / 180.0);
	edge(0, points, v4, v5, 120.0 * M_PI / 180.0);
	edge(0, points, v5, v6, M_PI);
	edge(0, points, v6, v1, -120.0 * M_PI / 180.0);
	points.push_back(v1);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderDrawLinesF(renderer, points.data(), points.size());
}

static void edge(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, float theta) {
	if (iter == 4) {
		points.push_back(v1);
		return;
	}

	float alpha = atan(sqrt(3) / 5);
	float edge_length = magnitude(v1, v2);
	float new_edge_length = (edge_length / 2) / sin(120.0 * M_PI / 180.0) * sin(60.0 * M_PI / 180.0 - alpha);

	SDL_FPoint va;
	va.x = v1.x + new_edge_length * cos(theta - alpha);
	va.y = v1.y + new_edge_length * sin(theta - alpha);

	SDL_FPoint vb;
	vb.x = va.x + new_edge_length * cos(theta + 60.0 * M_PI / 180.0 - alpha);
	vb.y = va.y + new_edge_length * sin(theta + 60.0 * M_PI / 180.0 - alpha);

	iter++;

	edge(iter, points, v1, va, theta - alpha);
	edge(iter, points, va, vb, theta + 60.0 * M_PI / 180.0 - alpha);
	edge(iter, points, vb, v2, theta - alpha);
}
