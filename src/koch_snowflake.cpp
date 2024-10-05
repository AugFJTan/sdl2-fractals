#include "fractals.h"
#include <cmath>
#include <vector>

void draw_triangle(int iter, SDL_Renderer* renderer, SDL_FPoint v1, SDL_FPoint v2, float length, float theta);

void koch_snowflake(SDL_Renderer* renderer) {
	float hypotenuse = 360.0;
	float height = hypotenuse * cos(30.0 * M_PI / 180.0);
	float width = hypotenuse;

	float x = SCREEN_WIDTH / 2;
	float y = (SCREEN_HEIGHT - height / 3) / 2;

	SDL_FPoint v1 = {x            , y - height / 2};
	SDL_FPoint v2 = {x - width / 2, y + height / 2};
	SDL_FPoint v3 = {x + width / 2, y + height / 2};

	const std::vector<SDL_Vertex> base =
	{
		{ v1, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
		{ v2, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
		{ v3, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
	};
	SDL_RenderGeometry(renderer, nullptr, base.data(), base.size(), nullptr, 0);

	draw_triangle(0, renderer, v1, v2, hypotenuse / 3, 120 * M_PI / 180.0);
	draw_triangle(0, renderer, v2, v3, hypotenuse / 3, 0);
	draw_triangle(0, renderer, v3, v1, hypotenuse / 3, 240 * M_PI / 180.0);
}

void draw_triangle(int iter, SDL_Renderer* renderer, SDL_FPoint v1, SDL_FPoint v2, float length, float theta) {
	if (iter == 4)
		return;

	float height = length * cos(30.0 * M_PI / 180.0);

	SDL_FPoint va = {0, height};
	SDL_FPoint vb = {-length/2, 0};
	SDL_FPoint vc = {length/2, 0};

	double mat_rot[2][2] = {
		{cos(theta), -sin(theta)},
		{sin(theta),  cos(theta)}
	};

	SDL_FPoint v_trans = midpoint(v1, v2);

	va = transform(va, mat_rot, v_trans);
	vb = transform(vb, mat_rot, v_trans);
	vc = transform(vc, mat_rot, v_trans);

	const std::vector<SDL_Vertex> base =
	{
		{ va, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
		{ vb, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
		{ vc, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
	};
	SDL_RenderGeometry(renderer, nullptr, base.data(), base.size(), nullptr, 0);

	iter++;

	draw_triangle(iter, renderer, va, vc, length / 3, theta - 60 * M_PI / 180.0);
	draw_triangle(iter, renderer, vb, va, length / 3, theta + 60 * M_PI / 180.0);
	draw_triangle(iter, renderer, v1, vb, length / 3, theta);
	draw_triangle(iter, renderer, vc, v2, length / 3, theta);
}
