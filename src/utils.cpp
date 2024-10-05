#include "utils.h"

SDL_FPoint midpoint(SDL_FPoint v1, SDL_FPoint v2) {
	return {(v1.x + v2.x) / 2, (v1.y + v2.y) / 2};
}

SDL_FPoint transform(SDL_FPoint v, double mat_rot[2][2], SDL_FPoint v_trans) {
	SDL_FPoint v_rot;
	v_rot.x = mat_rot[0][0] * v.x + mat_rot[0][1] * v.y;
	v_rot.y = mat_rot[1][0] * v.x + mat_rot[1][1] * v.y;

	SDL_FPoint v_res;
	v_res.x = v_rot.x + v_trans.x;
	v_res.y = v_rot.y + v_trans.y;

	return v_res;
}
