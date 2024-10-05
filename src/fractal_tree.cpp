#include "fractals.h"
#include <cmath>
#include <vector>

void draw_branch(SDL_Renderer* renderer, double theta, SDL_FPoint tip, float length, float width);
void branch(int iter, SDL_Renderer* renderer, double theta, SDL_FPoint tip, float length, float width);

void fractal_tree(SDL_Renderer* renderer) {
	float length = 100.0;
	float width = 20.0;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT - 40;

	SDL_FPoint root = {x, y};
	SDL_FPoint tip = {x, y-length};

	draw_branch(renderer, 0.0, root, length, width);

	branch(0, renderer, 0.0, tip, length * 0.8, width * 0.8);
	branch(0, renderer, 0.0, tip, length * 0.8, width * 0.8);
}

void draw_branch(SDL_Renderer* renderer, double theta, SDL_FPoint tip, float length, float width) {
	SDL_FPoint v1 = {width / 2, -length / 2};
	SDL_FPoint v2 = {-width / 2, -length / 2};
	SDL_FPoint v3 = {-width / 2, length / 2};
	SDL_FPoint v4 = {width / 2, length / 2};

	double mat_rot[2][2] = {
		{cos(theta), -sin(theta)},
		{sin(theta),  cos(theta)}
	};

	SDL_FPoint v_trans;
	v_trans.x = tip.x + length / 2 * sin(theta);
	v_trans.y = tip.y - length / 2 * cos(theta);

	v1 = transform(v1, mat_rot, v_trans);
	v2 = transform(v2, mat_rot, v_trans);
	v3 = transform(v3, mat_rot, v_trans);
	v4 = transform(v4, mat_rot, v_trans);

	const std::vector<SDL_Vertex> base =
	{
		{ v1, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
		{ v2, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
		{ v3, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
		{ v4, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
	};

	int indices[6] = {0, 1, 2, 2, 3, 0};

	SDL_RenderGeometry(renderer, nullptr, base.data(), base.size(), indices, 6);
}

void branch(int iter, SDL_Renderer* renderer, double theta, SDL_FPoint tip, float length, float width) {
	if (iter == 7)
		return;

	double ltheta = theta - (30 * M_PI / 180.0);
	double rtheta = theta + (30 * M_PI / 180.0);

	draw_branch(renderer, ltheta, tip, length, width);
	draw_branch(renderer, rtheta, tip, length, width);

	SDL_FPoint left;
	left.x = tip.x + length * sin(ltheta);
	left.y = tip.y - length * cos(ltheta);

	SDL_FPoint right;
	right.x = tip.x + length * sin(rtheta);
	right.y = tip.y - length * cos(rtheta);

	iter++;

	branch(iter, renderer, ltheta, left, length * 0.8, width * 0.8);
	branch(iter, renderer, rtheta, right, length * 0.8, width * 0.8);
}
