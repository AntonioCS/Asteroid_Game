#pragma once

constexpr auto SCALE_PLAYER_SHIP = 0.5;
constexpr auto PLAYER_SHIP_VERTEX_COUNT = 5;
constexpr auto PLAYER_SHIP_THRUST_VERTEX_COUNT = 3;
constexpr auto TOTAL_SHIP_VERTEX_COUNT = PLAYER_SHIP_VERTEX_COUNT + PLAYER_SHIP_THRUST_VERTEX_COUNT;
SDL_Point player_space_ship_ref[TOTAL_SHIP_VERTEX_COUNT] = {
	{32, 0},{-16, 18},{-10, 0},{-16, -18}, {32, 0},{-18,12}, {-32, 0}, {-18, -12}
};  // main ship
SDL_Point player_space_ship[TOTAL_SHIP_VERTEX_COUNT] = {
	{32, 0},{-16, 18},{-10, 0},{-16, -18}, {32, 0},{-18,12}, {-32, 0}, {-18, -12}
};  // main ship

SDL_Point player_ship_thrust[PLAYER_SHIP_THRUST_VERTEX_COUNT] = {
	{-18,12}, {-32, 0}, {-18, -12} // thrust triangle
};

SDL_Point intial_position_ship =
{ 400, 300 };

game_obj_velocity initial_velocity_ship =
{ 0.0, 0.0 };