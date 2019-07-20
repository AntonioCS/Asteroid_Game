#pragma once

#include <iostream>
#include <vector>
#include "bullet.hpp"

#include "_game_obj.hpp"

class enemy_ship : public game_obj
{
public:
	enemy_ship(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, bool _on_off, const int &_score, const double &_scale, const int &_visit_interval);
	~enemy_ship() = default;

	// launch enemy ship from either side of the screeen at a random angle
	void check_launch_enemy_ship();

	void destroy_enemy_ship(const Uint32 &current_start_time);

	bool check_enemy_ship_bullet_hit(player_bullet_list &bullets, const Uint32 &current_start_time);

	int score{ 0 };
	Uint32 start_time{ 0 };
	static int delay;
	static const int fire_border;
	int visit_interval;

private:
	int x{ -100 };
	int y{ -100 };
	double const scale;
};

class big_enemy_ship_construct {
public:
	big_enemy_ship_construct();
	~big_enemy_ship_construct() = default;
	static enemy_ship ship;
};

class small_enemy_ship_construct {
public:
	small_enemy_ship_construct();
	~small_enemy_ship_construct() = default;
	static enemy_ship ship;
};

	
