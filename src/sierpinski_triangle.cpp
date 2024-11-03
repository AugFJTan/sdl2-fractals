#include "fractals.h"
#include <cmath>
#include <vector>

static void sierpinski(int iter, SDL_Renderer* renderer, SDL_FPoint v1, SDL_FPoint v2, SDL_FPoint v3);

void sierpinski_triangle(SDL_Renderer* renderer) {
	float hypotenuse = 500.0;
	float height = hypotenuse * cos(30.0 * M_PI / 180.0);
	float width = hypotenuse;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT / 2;

	SDL_FPoint v1 = {x            , y - height / 2};
	SDL_FPoint v2 = {x - width / 2, y + height / 2};
	SDL_FPoint v3 = {x + width / 2, y + height / 2};

	const std::vector<SDL_Vertex> base =
	{
		{ v1, SDL_Color{ 0xff, 0x00, 0x00, 0xff }, SDL_FPoint{ 0 }, },
		{ v2, SDL_Color{ 0x00, 0x00, 0xff, 0xff }, SDL_FPoint{ 0 }, },
		{ v3, SDL_Color{ 0x00, 0xff, 0x00, 0xff }, SDL_FPoint{ 0 }, },
	};
	SDL_RenderGeometry(renderer, nullptr, base.data(), base.size(), nullptr, 0);

	sierpinski(0, renderer, v1, v2, v3);
}

static void sierpinski(int iter, SDL_Renderer* renderer, SDL_FPoint v1, SDL_FPoint v2, SDL_FPoint v3) {
	if (iter == 6)
		return;

	SDL_FPoint va = midpoint(v1, v2);
	SDL_FPoint vb = midpoint(v2, v3);
	SDL_FPoint vc = midpoint(v3, v1);

	const std::vector<SDL_Vertex> hole =
	{
		{ va, SDL_Color{ 0x7f, 0x7f, 0x7f, 0xff }, SDL_FPoint{ 0 }, },
		{ vb, SDL_Color{ 0x7f, 0x7f, 0x7f, 0xff }, SDL_FPoint{ 0 }, },
		{ vc, SDL_Color{ 0x7f, 0x7f, 0x7f, 0xff }, SDL_FPoint{ 0 }, },
	};
	SDL_RenderGeometry(renderer, nullptr, hole.data(), hole.size(), nullptr, 0);

	iter++;

	sierpinski(iter, renderer, v1, va, vc);
	sierpinski(iter, renderer, va, v2, vb);
	sierpinski(iter, renderer, vc, vb, v3);
}
