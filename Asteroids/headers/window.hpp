#pragma once
#include<string>
#include<SDL.h>

#include "sounds.hpp"

constexpr auto window_X = 800;
constexpr auto window_Y = 600;

class window {
public:
	window(const std::string &_title, int _width, int _height);
	~window();
	void poll_all_events(const Uint8 *keystate);
	void x_close_chk(SDL_Event &event);
	void clear() const;
	int get_refresh_rate();
		
	inline bool is_closed() const { return closed; }

private:
	bool init();

private:
	std::string title;
	int width{ window_X };
	int height{ window_Y };
	bool closed{ false };

	SDL_Window *asteroid_window = nullptr;

public:
	static SDL_Renderer *renderer;
	bool space_key_release{ false };
};
