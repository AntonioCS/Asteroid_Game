#pragma once

constexpr auto TOTAL_ROCKS = BIG_ROCK_COUNT + MEDIUM_ROCK_COUNT + SMALL_ROCK_COUNT;
constexpr auto ROCK_VERTEX_COUNT = 12;

SDL_Point rocks[TOTAL_ROCKS][ROCK_VERTEX_COUNT];

constexpr auto ROCK_TYPE_COUNT = 4;

constexpr auto SCALE_SHOW_LIVES = 1.0;
constexpr auto SHOW_LIVES_VERTEX_COUNT = 4;
constexpr auto SHOW_LIVES_COUNT = 10;
constexpr auto START_LIVES_NUM = 3;
constexpr SDL_Point GAME_OVER_MSG = { 340, 280 };

SDL_Point show_lives[SHOW_LIVES_COUNT][SHOW_LIVES_VERTEX_COUNT];

SDL_Point show_lives_ref[SHOW_LIVES_VERTEX_COUNT] = {
		{-10, 10},{0, -10},{10, 10},{-10, 10}
};

SDL_Point intial_position_show_lives[SHOW_LIVES_COUNT] = { 
	{100, 100},
	{130, 100},
	{160, 100},
	{190, 100},
	{220, 100},
	{250, 100},
	{280, 100},
	{310, 100},
	{340, 100},
	{370, 100}
};

bool show_show_lives[SHOW_LIVES_COUNT]{ true, true, true, false, false, false, false, false, false, false };

