#pragma once

#include <iostream>
#include <vector>
#include <SDL_image.h>

#include "window.hpp"

class show_remain_lives {
public:
	show_remain_lives(SDL_Point *_vertices, const SDL_Point &_position, bool _on_off);

	~show_remain_lives() = default;

	void draw() const;

	SDL_Point *vertices;
	SDL_Point position;
	bool on_off;
};

class remaining_lives {
public:
	remaining_lives();
	~remaining_lives() = default;
	std::vector<show_remain_lives> list;
};
