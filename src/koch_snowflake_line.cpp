#include "fractals.h"
#include <cmath>
#include <vector>

static void edge(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, float theta);

void koch_snowflake_line(SDL_Renderer* renderer) {
	float hypotenuse = 360.0;
	float height = hypotenuse * cos(30.0 * M_PI / 180.0);
	float width = hypotenuse;

	float x = SCREEN_WIDTH / 2;
	float y = (SCREEN_HEIGHT - height / 3) / 2;

	SDL_FPoint v1 = {x            , y - height / 2};
	SDL_FPoint v2 = {x - width / 2, y + height / 2};
	SDL_FPoint v3 = {x + width / 2, y + height / 2};

	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

	std::vector<SDL_FPoint> points;

	edge(0, points, v1, v2, -120 * M_PI / 180.0);
	edge(0, points, v2, v3, 0);
	edge(0, points, v3, v1, 120 * M_PI / 180.0);
	points.push_back(v1);

	SDL_RenderDrawLinesF(renderer, points.data(), points.size());
}

static void edge(int iter, std::vector<SDL_FPoint> &points, SDL_FPoint v1, SDL_FPoint v2, float theta) {
	if (iter == 4) {
		points.push_back(v1);
		return;
	}

	float edge_length = magnitude(v1, v2) / 3;

	SDL_FPoint va;
	va.x = v1.x + edge_length * cos(theta);
	va.y = v1.y - edge_length * sin(theta);

	SDL_FPoint vb;
	vb.x = va.x + edge_length * cos(theta - 60 * M_PI / 180.0);
	vb.y = va.y - edge_length * sin(theta - 60 * M_PI / 180.0);

	SDL_FPoint vc;
	vc.x = vb.x + edge_length * cos(theta + 60 * M_PI / 180.0);
	vc.y = vb.y - edge_length * sin(theta + 60 * M_PI / 180.0);

	iter++;

	/*
		Vertex layout:
		           vb
		          /  \
		         *    *
		        /      \
		v1--*--va      vc--*--v2
	*/
	edge(iter, points, v1, va, theta);
	edge(iter, points, va, vb, theta - 60 * M_PI / 180.0);
	edge(iter, points, vb, vc, theta + 60 * M_PI / 180.0);
	edge(iter, points, vc, v2, theta);
}
