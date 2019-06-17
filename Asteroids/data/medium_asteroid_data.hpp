#pragma once

#include <algorithm> // std::fill_n

constexpr auto SCALE_MEDIUM_ROCK = 0.85;
constexpr auto MEDIUM_ROCK_VERTEX_COUNT = 12;
constexpr auto MEDIUM_ROCK_TYPE_COUNT = 4;
constexpr auto MEDIUM_ROCK_COUNT = 24;
constexpr auto MEDIUM_ROCK = 'm';
constexpr auto MEDIUM_ROCK_SPEED = 1.5;

SDL_Point medium_rocks[MEDIUM_ROCK_COUNT][MEDIUM_ROCK_VERTEX_COUNT];
SDL_Point medium_rocks_ref[MEDIUM_ROCK_TYPE_COUNT][MEDIUM_ROCK_VERTEX_COUNT] = {
	{
		{-25, -5},{-5, -25},{0, -20},{12, -25},{25,-15},{10, 0},{25, 5},{10, 25},{0, 15},{-15, 25},{-25, 0},{-25,-5}
	},
	{
		{-25, 0},{-25, -15},{-5, -15},{-10, -25},{10,-25},{25,-5},{5, 5},{25, 15},{15,25},{0, 20},{-12, 25},{-25, 0}
	},
	{
		{-25, 0},{-20, -15},{-5, -25},{10, -20},{7,-7},{25, 0},{17, 15},{5, 15},{0,25},{-20, 15},{-25, 0},{-25,0}
	},
	{
		{-25, 10},{-15, 0},{-25, -10},{-10, -25},{10,-25},{25,-10},{25, 5},{10, 25},{0,25},{-2, 10},{-15, 25},{-25,10}
	}
};

/*SDL_Point intial_position_medium_rocks[MEDIUM_ROCK_COUNT] = {
	 { 400, 300 }, { 200, 400 },  { 300, 300 }, { 500, 600 }, {500, 500}
};*/

SDL_Point intial_position_medium_rocks[MEDIUM_ROCK_COUNT] = {
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0}
};

game_obj_velocity initial_velocity_medium_rocks[MEDIUM_ROCK_COUNT] = {
	{ 0, MEDIUM_ROCK_SPEED }, { 0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED},
	{ 0, MEDIUM_ROCK_SPEED }, { 0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED},
	{ 0, MEDIUM_ROCK_SPEED }, { 0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED},
	{ 0, MEDIUM_ROCK_SPEED }, { 0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED }, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED}, {0, MEDIUM_ROCK_SPEED},
};


bool show_medium_rocks[MEDIUM_ROCK_COUNT]{
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
};
