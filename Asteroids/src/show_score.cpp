#include "show_score.hpp"

score::score(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &show_score, const SDL_Color &color)
{
	for (int i = 0; i < 10; ++i) {
		score_texture = loadFont(renderer, font_path, font_size, std::to_string(i), color);
		SDL_QueryTexture(score_texture, nullptr, nullptr, &score_rect.w, &score_rect.h);
		texture_number.push_back(score_texture);
	}
}

void score::display(const int &x, const int &y, SDL_Renderer *renderer, const std::string &player_score, const int &font_size)
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