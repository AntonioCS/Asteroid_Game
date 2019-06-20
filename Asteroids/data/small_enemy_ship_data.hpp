#pragma once

constexpr auto SCALE_SMALL_ENEMY_SHIP = 0.75;

constexpr auto SMALL_ENEMY_SHIP_TIMING = 20 * 1000;

constexpr auto SMALL_ENEMY_SHIP_VERTEX_COUNT = 12;
constexpr auto SMALL_ENEMY_SHIP_SPEED = 3.0;
constexpr auto SMALL_ENEMY_SHIP_SCORE = 1000;
constexpr auto SMALL_ENEMY_SHIP_FIRE_BORDER = 100;
constexpr auto ENEMY_SHIP_FIRE_DELAY = 200;

SDL_Point small_enemy_ship_ref[SMALL_ENEMY_SHIP_VERTEX_COUNT] = {
		{-20, 0},{-10, -10},{-8, -20},{8, -20},{10,-10},{20,0},{10, 10},{-10, 10},{-20,0}, {20,0}, {10, -10}, {-10,-10}
};

SDL_Point intial_position_small_enemy_ship = { 0, 200 };

game_obj_velocity initial_velocity_small_enemy_ship =
{ 0.0, SMALL_ENEMY_SHIP_SPEED };

bool show_small_enemy_ship{ false };



