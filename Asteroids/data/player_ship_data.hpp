#pragma once

constexpr auto PI = 3.14159265359;

// Ship Specification
constexpr auto SHIP_THRUST = 0.05;
constexpr auto SHIP_VELOCITY_LIMIT = 4.0;
constexpr auto SHIP_ROTATION_SPEED = 0.04;
constexpr auto SHIP_MASS = 10;

constexpr auto SCALE_PLAYER_SHIP = 0.5;
constexpr auto PLAYER_SHIP_VERTEX_COUNT = 5;
constexpr auto PLAYER_SHIP_THRUST_VERTEX_COUNT = 3;
constexpr auto TOTAL_SHIP_VERTEX_COUNT = PLAYER_SHIP_VERTEX_COUNT + PLAYER_SHIP_THRUST_VERTEX_COUNT;

SDL_Point player_space_ship[TOTAL_SHIP_VERTEX_COUNT] = { {32, 0},{-16, 18},{-10, 0},{-16, -18}, {32, 0},{-18,12}, {-32, 0}, {-18, -12} };  // main ship static vertices position

SDL_Point player_space_ship_ref[TOTAL_SHIP_VERTEX_COUNT] = {
	{32, 0},{-16, 18},{-10, 0},{-16, -18}, {32, 0},{-18,12}, {-32, 0}, {-18, -12}
};  // main ship dynamic vertices position


SDL_Point player_ship_thrust[PLAYER_SHIP_THRUST_VERTEX_COUNT] = {
	{-18,12}, {-32, 0}, {-18, -12} // thrust triangle vertices for drawing
};

SDL_Point intial_position_ship = { 400 / SCALE_PLAYER_SHIP , 300 / SCALE_PLAYER_SHIP };

game_obj_velocity initial_velocity_ship = { 0.0, 0.0 };

SDL_Point space_ship[TOTAL_SHIP_VERTEX_COUNT];

constexpr auto START_LIVES_NUM = 3;
constexpr auto SCORE_FOR_EXTRA_SHIP = 10000;
constexpr auto SHIP_DRAG = 1.00;
const std::vector<int> EXPLOSION_DRAW_VERTICES_REF = { 0,1,1,2,2,3,3,0 };
constexpr auto EXPLOSION_PIECES_ROTATION_SPEED = 0.05;
constexpr auto EXPLOSION_RADIUS_DURATION = 200;