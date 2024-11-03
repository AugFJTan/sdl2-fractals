#include "fractals.h"
#include <vector>

static void sierpinski(int iter, SDL_Renderer* renderer, SDL_FPoint pos, float length);

void sierpinski_carpet(SDL_Renderer* renderer) {
	float length = 420.0;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT / 2;

	SDL_FPoint v1 = {x + length / 2, y - length / 2};
	SDL_FPoint v2 = {x - length / 2, y - length / 2};
	SDL_FPoint v3 = {x - length / 2, y + length / 2};
	SDL_FPoint v4 = {x + length / 2, y + length / 2};

	const std::vector<SDL_Vertex> base =
	{
		{ v1, SDL_Color{ 0x00, 0xff, 0x00, 0xff }, SDL_FPoint{ 0 }, },
		{ v2, SDL_Color{ 0xff, 0x00, 0x00, 0xff }, SDL_FPoint{ 0 }, },
		{ v3, SDL_Color{ 0x00, 0xff, 0x00, 0xff }, SDL_FPoint{ 0 }, },
		{ v4, SDL_Color{ 0x00, 0x00, 0xff, 0xff }, SDL_FPoint{ 0 }, },
	};

	int indices[6] = {0, 1, 2, 2, 3, 0};

	SDL_RenderGeometry(renderer, nullptr, base.data(), base.size(), indices, 6);

	sierpinski(0, renderer, v2, length);
}

static void sierpinski(int iter, SDL_Renderer* renderer, SDL_FPoint pos, float length) {
	if (iter == 5)
		return;

	float new_length = length / 3;

	SDL_Rect hole;
	hole.x = pos.x + new_length;
	hole.y = pos.y + new_length;
	hole.w = new_length;
	hole.h = new_length;

	SDL_RenderFillRect(renderer, &hole);

	iter++;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 1 && j == 1)
				continue;
			sierpinski(iter, renderer, {pos.x + new_length * j, pos.y + new_length * i}, new_length);
		}
	}
}
