#pragma once

#include <iostream>
#include <SDL_image.h>

class show_remain_lives {
public:
	show_remain_lives(SDL_Point *_vertices, SDL_Point _position, bool _on_off) :
		vertices { _vertices },
		position { _position },
		on_off { _on_off }
	
	{
		for (int i = 0; i < SHOW_LIVES_VERTEX_COUNT; ++i) {
			vertices[i].x += position.x;
			vertices[i].y += position.y;
		}
	}

	~show_remain_lives() = default;

	virtual void draw() const {
		SDL_SetRenderDrawColor(window::renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLines(window::renderer, vertices, SHOW_LIVES_VERTEX_COUNT);
	}

	SDL_Point *vertices;
	SDL_Point position;
	bool on_off;
};
