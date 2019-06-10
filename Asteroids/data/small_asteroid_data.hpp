#pragma once

#include <algorithm> // std::fill_n

constexpr auto SCALE_SMALL_ROCK = 0.75;
constexpr auto SMALL_ROCK_VERTEX_COUNT = 12;
constexpr auto SMALL_ROCK_TYPE_COUNT = 4;
constexpr auto SMALL_ROCK_COUNT = 48;
constexpr auto SMALL_ROCK = 's';
constexpr auto SMALL_ROCK_SPEED = 3.0;

SDL_Point small_rocks[SMALL_ROCK_COUNT][SMALL_ROCK_VERTEX_COUNT];
SDL_Point small_rocks_ref[SMALL_ROCK_TYPE_COUNT][SMALL_ROCK_VERTEX_COUNT] = {
	{
		{-12, -3},{-3, -12},{0, -10},{6, -12},{12,-8},{5, 0},{12, 3},{5, 12},{0, 8},{-7, 12},{-12, 0},{-12,-3}
	},
	{
		{-12, 0},{-12, -8},{-3, -7},{-5, -12},{5,-12},{12,-3},{3, 2},{12, 8},{7,12},{0, 10},{-6, 12},{-12, 0}
	},
	{
		{-12, 0},{-10, -8},{-3, -12},{5, -10},{3,-4},{12, 0},{8, 7},{3, 7},{0,12},{-10, 8},{-12, 0},{-12,0}
	},
	{
		{-12, 5},{-8, 0},{-12, -5},{-5, -12},{5,-12},{12,-5},{12, 3},{5, 12},{0,12},{-1, 5},{-8, 12},{-12,5}
	}
};

SDL_Point intial_position_small_rocks[SMALL_ROCK_COUNT] = {
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0},
	 { 0, 0 }, { 0, 0 },  { 0, 0 }, { 0, 0 }, {0, 0}, {0,0}
};

game_obj_velocity initial_velocity_small_rocks[SMALL_ROCK_COUNT] = {
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
	{ 0, SMALL_ROCK_SPEED }, { 0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED }, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED}, {0, SMALL_ROCK_SPEED},
};


bool show_small_rocks[SMALL_ROCK_COUNT]{
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
	false, false, false, false, false, false,
};
