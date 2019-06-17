#pragma once

constexpr int new_level_delay = 5 * 1000;

class control {
public:
	control() = default;
	~control() = default;

	int level{0};
	bool one_left{ true };
	bool asteroid_too_close_to_reset_position{ false };
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	int screen_refresh_rate{ 0 }; // every xx of a second

	Uint32 start_time{ 0 };
	Uint32 end_time{ 0 };
	Uint32 level_start_time = SDL_GetTicks();
	Uint32 level_new_time = SDL_GetTicks();
	Uint32 small_ship_start_time = level_start_time;
	Uint32 big_ship_start_time = level_start_time;
	Uint32 new_level_delay = 2 * 1000;
	bool new_level_chk{true};
};



