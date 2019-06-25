#pragma once

constexpr auto SCALE_BIG_ENEMY_SHIP = 0.9;

constexpr auto BIG_ENEMY_SHIP_TIMING = 10 * 1000; // 20 seconds

constexpr auto BIG_ENEMY_SHIP_VERTEX_COUNT = 12;
constexpr auto BIG_ENEMY_SHIP_SPEED = 1.5;
constexpr auto BIG_ENEMY_SHIP_SCORE = 200;



SDL_Point big_enemy_ship_ref[BIG_ENEMY_SHIP_VERTEX_COUNT] = {
		{-20, 0},{-10, -10},{-7, -20},{7, -20},{10,-10},{20,0},{10, 10},{-10, 10},{-20,0}, {20,0}, {10, -10}, {-10,-10}
};

SDL_Point intial_position_big_enemy_ship = { 0, window_Y / 6 };

game_obj_velocity initial_velocity_big_enemy_ship =
{ 0.0, BIG_ENEMY_SHIP_SPEED };

bool show_big_enemy_ship{ false };