#include "fractals.h"
#include <vector>

void draw_pattern(int iter, SDL_Renderer* renderer, SDL_FPoint pos, float length);

void box_factal(SDL_Renderer* renderer) {
	float length = 420.0;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT / 2;

	SDL_FPoint v1 = {x + length / 2, y - length / 2};
	SDL_FPoint v2 = {x - length / 2, y - length / 2};
	SDL_FPoint v3 = {x - length / 2, y + length / 2};
	SDL_FPoint v4 = {x + length / 2, y + length / 2};

	const std::vector<SDL_Vertex> base =
	{
		{ v1, SDL_Color{ 0x00, 0xff, 0xff, 0xff }, SDL_FPoint{ 0 }, },
		{ v2, SDL_Color{ 0xff, 0x00, 0x00, 0xff }, SDL_FPoint{ 0 }, },
		{ v3, SDL_Color{ 0xff, 0xff, 0x00, 0xff }, SDL_FPoint{ 0 }, },
		{ v4, SDL_Color{ 0x00, 0x00, 0xff, 0xff }, SDL_FPoint{ 0 }, },
	};

	int indices[6] = {0, 1, 2, 2, 3, 0};

	SDL_RenderGeometry(renderer, nullptr, base.data(), base.size(), indices, 6);

	draw_pattern(0, renderer, v2, length);
}

void draw_pattern(int iter, SDL_Renderer* renderer, SDL_FPoint pos, float length) {
	if (iter == 4)
		return;

	float new_length = length / 3;

	int cell_rules[3][3] = {
		{1, 0, 1},
		{0, 1, 0},
		{1, 0, 1}
	};

	iter++;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float x = pos.x + new_length * j;
			float y = pos.y + new_length * i;

			if (cell_rules[i][j]) {
				draw_pattern(iter, renderer, {x, y}, new_length);
			} else {
				SDL_FRect hole;
				hole.x = x;
				hole.y = y;
				hole.w = new_length;
				hole.h = new_length;
				SDL_RenderFillRectF(renderer, &hole);
			}
		}
	}
}
