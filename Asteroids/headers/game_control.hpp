#pragma once

class control {
public:
	control() = default;
	~control() = default;

	int level{0};
	bool one_left{ true };

	Uint32 start_time{ 0 };
	Uint32 end_time{ 0 };
	Uint32 level_start_time = SDL_GetTicks();
	Uint32 small_ship_start_time = level_start_time;
	Uint32 big_ship_start_time = level_start_time;

};
