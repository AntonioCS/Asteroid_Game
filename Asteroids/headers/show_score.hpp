#pragma once

#include<SDL_ttf.h>
#include<SDL.h>
#include<string>
#include<vector>

#include "_message.hpp"

class score : public message {
public:
	score(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &show_score, const SDL_Color &color)
	{
		for (int i = 0; i < 10; ++i) {
			score_texture = loadFont(renderer, font_path, font_size, std::to_string(i), color);
			SDL_QueryTexture(score_texture, nullptr, nullptr, &score_rect.w, &score_rect.h);
			texture_number.push_back(score_texture);
		}
	}
	~score() = default;

	void display(int x, int y, SDL_Renderer *renderer, std::string player_score, int &font_size)
	{
		score_rect.x = x;
		score_rect.y = y;
		for (auto i : player_score) {
			score_rect.x += font_size - letter_spacing;
			ia = i - '0';
			if (ia >= 0 && ia <= 9) {
				SDL_RenderCopy(renderer, texture_number[ia], nullptr, &score_rect);
			}
		}
		score_rect.x = x;
	}

private:
	SDL_Texture *score_texture = nullptr;
	mutable SDL_Rect score_rect;
	std::vector<SDL_Texture*> texture_number; // this is a vector of pointers
	//std::string p_score;
	int ia{ 0 }, letter_spacing{ 4 };
};