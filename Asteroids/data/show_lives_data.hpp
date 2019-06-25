#pragma once

constexpr auto SCALE_SHOW_LIVES = 1.0;
constexpr int SHOW_LIVES_VERTEX_COUNT = 4;
constexpr int SHOW_LIVES_COUNT = 10;
constexpr int START_LIVES_NUM = 3;
constexpr SDL_Point GAME_OVER_MSG = { 340, 280 };

SDL_Point show_lives[SHOW_LIVES_COUNT][SHOW_LIVES_VERTEX_COUNT];

SDL_Point show_lives_ref[SHOW_LIVES_VERTEX_COUNT] = {
		{-10, 10},{0, -10},{10, 10},{-10, 10}
};

SDL_Point intial_position_show_lives[SHOW_LIVES_COUNT] = { 
	{window_X / 8, window_Y / 6},
	{30+window_X / 8, window_Y / 6},
	{60 + window_X / 8, window_Y / 6},
	{90 + window_X / 8, window_Y / 6},
	{120 + window_X / 8, window_Y / 6},
	{150 + window_X / 8, window_Y / 6},
	{180 + window_X / 8, window_Y / 6},
	{210 + window_X / 8, window_Y / 6},
	{240 + window_X / 8, window_Y / 6},
	{270 + window_X / 8, window_Y / 6}
};

bool show_show_lives[SHOW_LIVES_COUNT]{ true, true, true, false, false, false, false, false, false, false };

