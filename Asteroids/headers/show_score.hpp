#pragma once

#include<SDL_ttf.h>
#include<SDL.h>
#include<string>
#include<vector>

#include "_message.hpp"

class score : public message {
public:
	score(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &show_score, const SDL_Color &color);
	~score() = default;

	void display(const int &x, const int &y, SDL_Renderer *renderer, const std::string &player_score, const int &font_size);

private:
	SDL_Texture *score_texture = nullptr;
	mutable SDL_Rect score_rect; // review why made mutable
	std::vector<SDL_Texture*> texture_number; // this is a vector of pointers
	int ia{ 0 };
	int const letter_spacing{ 4 };
};

