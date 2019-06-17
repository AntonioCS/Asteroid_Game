#include "show_remain_lives.hpp"

#include "show_lives_data.hpp"

show_remain_lives::show_remain_lives(SDL_Point *_vertices, const SDL_Point &_position, bool _on_off) :
	vertices{ _vertices },
	position{ _position },
	on_off{ _on_off }

{
	for (int i = 0; i < SHOW_LIVES_VERTEX_COUNT; ++i) {
		vertices[i].x += position.x;
		vertices[i].y += position.y;
	}
}

void show_remain_lives::draw() const {
	SDL_SetRenderDrawColor(window::renderer, 200, 200, 200, 255);
	SDL_RenderDrawLines(window::renderer, vertices, SHOW_LIVES_VERTEX_COUNT);
}

remaining_lives::remaining_lives() {
	for (int i = 0; i < SHOW_LIVES_COUNT; ++i) {
		for (int j = 0; j < SHOW_LIVES_VERTEX_COUNT; ++j) {
			show_lives[i][j] = show_lives_ref[j];
		}
	}
	std::vector<show_remain_lives> show_remain_lives_list;
	for (int i = 0; i < SHOW_LIVES_COUNT; ++i) {
		show_remain_lives show_remain_lives(show_lives[i], intial_position_show_lives[i], show_show_lives[i]);
		list.push_back(show_remain_lives);
	}
}