#include "fractals.h"
#include <cmath>

static void branch(int iter, SDL_Renderer* renderer, double theta, SDL_FPoint tip, float length);

void fractal_tree_line(SDL_Renderer* renderer) {
	float length = 100.0;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT - 40;

	SDL_FPoint root = {x, y};
	SDL_FPoint tip = {x, y-length};

	SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);

	SDL_RenderDrawLineF(renderer, root.x, root.y, root.x, root.y - length);

	branch(0, renderer, 0.0, tip, length * 0.8);
	branch(0, renderer, 0.0, tip, length * 0.8);
}

static void branch(int iter, SDL_Renderer* renderer, double theta, SDL_FPoint tip, float length) {
	if (iter == 7)
		return;

	double ltheta = theta - (30 * M_PI / 180.0);
	double rtheta = theta + (30 * M_PI / 180.0);

	SDL_FPoint left;
	left.x = tip.x + length * sin(ltheta);
	left.y = tip.y - length * cos(ltheta);

	SDL_FPoint right;
	right.x = tip.x + length * sin(rtheta);
	right.y = tip.y - length * cos(rtheta);

	SDL_RenderDrawLineF(renderer, tip.x, tip.y, left.x, left.y);
	SDL_RenderDrawLineF(renderer, tip.x, tip.y, right.x, right.y);

	iter++;

	branch(iter, renderer, ltheta, left, length * 0.8);
	branch(iter, renderer, rtheta, right, length * 0.8);
}
