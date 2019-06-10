#pragma once

#include<SDL_ttf.h>
#include<SDL.h>
#include<string>
#include<vector>

#include "_message.hpp"

class text_message : public message {
public:
	text_message(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color)
	{
		title_texture = loadFont(renderer, font_path, font_size, message, color);
		SDL_QueryTexture(title_texture, nullptr, nullptr, &title_rect.w, &title_rect.h);
	}

	~text_message() = default;

	void display(int x, int y, SDL_Renderer *renderer) const
	{
		title_rect.x = x;
		title_rect.y = y;
		SDL_RenderCopy(renderer, title_texture, nullptr, &title_rect);
	}

private:
	SDL_Texture *title_texture = nullptr;
	mutable SDL_Rect title_rect;
};