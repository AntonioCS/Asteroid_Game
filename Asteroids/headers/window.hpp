#pragma once
#include<string>
#include <SDL2/SDL.h>

constexpr auto window_X = 2 * 1920 / 3;
constexpr auto window_Y = 2* 1080 / 3;

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

	std::string title;
	int width{ window_X };
	int height{ window_Y };
	bool closed{ false };

	SDL_Window *asteroid_window = nullptr;

public:
	static SDL_Renderer *renderer;
	bool space_key_release{ false };
	bool hyperspace_key_release{ false };
};
