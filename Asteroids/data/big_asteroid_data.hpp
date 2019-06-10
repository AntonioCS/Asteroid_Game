#pragma once

constexpr auto SCALE_BIG_ROCK = 0.75;
constexpr auto BIG_ROCK_VERTEX_COUNT = 12;
constexpr auto BIG_ROCK_TYPE_COUNT = 4;
constexpr auto BIG_ROCK_START_COUNT = 1;
constexpr auto BIG_ROCK_COUNT = 12;
constexpr auto BIG_ROCK = 'b';
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
	 { 200, 400 }, { 300, 200 },  { 100, 100 }, { 600, 500 }, {200, 600}, {-100,-100},
	 { -100,-100 }, { -100,-100 }, {-100,-100 }, { -100,-100 }, { -100,-100 }, { -100,-100 }
};

game_obj_velocity initial_velocity_big_rocks[BIG_ROCK_COUNT] = {
	{ PI / 4.0, BIG_ROCK_SPEED},
//	{ PI / 2.0 , BIG_ROCK_SPEED},
	{ 2.0 * PI / 3.0, BIG_ROCK_SPEED},
//	{ PI , BIG_ROCK_SPEED },
	{ 5.0 * PI / 4.0, BIG_ROCK_SPEED },
//	{ 3 * PI / 2, BIG_ROCK_SPEED },
	{ 7.0 * PI / 4.0, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED },
	{ 0.0, BIG_ROCK_SPEED }
};


bool show_big_rocks[BIG_ROCK_COUNT]{
	true, false, false, false, false, false,
	false, false, false, false,false, false,
};
