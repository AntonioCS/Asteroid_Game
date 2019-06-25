#pragma once

constexpr auto PI = 3.14159265359;

constexpr auto TOTAL_ROCKS = 12 + 24 + 48;
constexpr auto ROCK_VERTEX_COUNT = 12;
constexpr auto ROCK_TYPE_COUNT = 4;
constexpr auto BIG_ROCK_START_COUNT = 4;

SDL_Point rocks[TOTAL_ROCKS][ROCK_VERTEX_COUNT];

constexpr auto SCALE_BIG_ROCK = 0.6;
constexpr auto BIG_ROCK_VERTEX_COUNT = 12;
constexpr auto BIG_ROCK_TYPE_COUNT = 4;

constexpr auto BIG_ROCK_COUNT = 12;
constexpr char BIG_ROCK = 'b';
constexpr auto BIG_ROCK_SPEED = 1.0;

SDL_Point big_rocks[BIG_ROCK_COUNT][BIG_ROCK_VERTEX_COUNT];
SDL_Point big_rocks_ref[BIG_ROCK_TYPE_COUNT][BIG_ROCK_VERTEX_COUNT] = {
	{
		{-50, 20},{-30, 0},{-50, -20},{-20, -50},{20,-50},{50,-20},{50, 10},{20, 50},{0,50},{-5, 20},{-30, 50},{-50,20}
	},
	{
		{-50, 0},{-50, -30},{-10, -30},{-20, -50},{20,-50},{50,-10},{10, 10},{50, 30},{30,50},{0, 40},{-25, 50},{-50, 0}
	},
	{
		{-50, 0},{-40, -30},{-10, -50},{20, -40},{15,-15},{50, 0},{35, 30},{10, 30},{0,50},{-40, 30},{-50, 0},{-50,0}
	},
	{
		{-50, 0},{-50, -30},{-10, -30},{-20, -50},{20,-50},{50,-10},{10, 10},{50, 30},{30,50},{0, 40},{-25, 50},{-50, 0}
	}
};

SDL_Point intial_position_big_rocks[BIG_ROCK_COUNT] = {
	{ window_X / 8, 3 * window_Y / 6}, //  change all these to window relative
	{ 5 * window_X / 8 , window_Y  / 6 },
	{ window_X / 8 , window_Y / 6},
	{6 * window_X / 8 , 5 * window_Y / 6},
	{2*window_X / 8 , 3 * window_Y / 6},
	{window_X / 8 , 3 * window_Y / 6},

	{2*window_X / 8 , 2 * window_Y / 6},
	{ 150,150 },
	
	{ 250, 250 },

	{3 * window_X / 8 , 3 * window_Y / 6},
	{ 550,550 },
    {3*window_X / 4 , 5 * window_Y / 8},
};

game_obj_velocity initial_velocity_big_rocks[BIG_ROCK_COUNT] = {
	{ PI / 4.0, BIG_ROCK_SPEED},
	{ PI / 2.0 , BIG_ROCK_SPEED},
	{ 2.0 * PI / 3.0, BIG_ROCK_SPEED},
	{ PI/1.75, BIG_ROCK_SPEED },
	{ 5.0 * PI / 4.0, BIG_ROCK_SPEED },
	{ 3.0 * PI / 2.0, BIG_ROCK_SPEED },
	{ 7.0 * PI / 4.0, BIG_ROCK_SPEED },
	{ PI / 2.0, BIG_ROCK_SPEED },
	{ PI / 2.1, BIG_ROCK_SPEED },
	{ PI / 2.2, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED }
};


bool show_big_rocks[BIG_ROCK_COUNT]{
	true, true, true, true, false, false,
	false, false, false, false, false, false
};
