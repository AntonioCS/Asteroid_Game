#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "_game_obj.hpp"

struct ship_specification {
	static const double thrust;
	static const double velocity_limit;
	static const double ship_rotate_speed;
	static const double mass;
	double acceleration{ thrust / mass };
};

struct explode_shape {
	double line_length;
	pointd line_centre;
	double angle;
};

class player_ship : public game_obj
{
public:
	player_ship(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, const double &_scale);
	~player_ship() = default;

	void get_centre_rotation();
	void rotate_ship(const double &ship_orientation);
	void check_rotational_limits(double &ship_orientation);
	void rotate_left();
	void rotate_right();
	void thrust();
	void reset_pos();
	void hyperspace();
	void got_hit();
	void split_apart();
	virtual void draw() const override;
	bool earn_life();
	void new_game();

	static double drag; 
	double ship_orientation;
	static bool show_thrust;
	static int score;
	static int lives;
	static const int max_lives;
	static bool reset;
	static int extra_ship;
	static int hyperspace_num;
	
private:
	double av_vel_old;
	static pointd ship_momentum;
	static pointd thrust_force;
	double motion_orientation_delta_angle;
	double sideways_velocity;
	ship_specification ship_specification;
	double cos_a{};
	double sin_a{};
	static std::vector<int> vert_index;
	double explode_orientation;
	std::vector<explode_shape> explode_line_list;
	static std::vector<pointd> explode_step;
	static double explosion_rotation_spd;
	static std::vector<double> explosion_part_rotation;
	static int explode_count;
	static int expode_duration;
	pointd sc;
	static double rotated_space_ship_X[];
	static double rotated_space_ship_Y[];
	static SDL_Point explode_vertices[];
	double scale;
};

class ship_construct {
public:
	ship_construct();
	~ship_construct() = default;
	static player_ship ship;
};
