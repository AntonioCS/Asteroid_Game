#pragma once

#include <iostream>
#include "window.hpp"

class message {
public:

	SDL_Texture *loadFont(SDL_Renderer *renderer,
		const std::string &font_path,
		int font_size,
		const std::string &show_win,
		const SDL_Color &color)
	{
		TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
		std::cout << "font: " << font << "\n";
		if (!font) {
			std::cerr << "Failed to load font.\n";
		}
		auto win_surface = TTF_RenderText_Solid(font, show_win.c_str(), color);

		if (!win_surface) {
			std::cerr << "Failed to create score surface.\n";
		}
		auto win_texture = SDL_CreateTextureFromSurface(renderer, win_surface);
		if (!win_texture) {
			std::cerr << "Failed to create score texture.\n";
		}
		SDL_FreeSurface(win_surface);
		return win_texture;
	}
	~message() = default;
};