#pragma once

#include <iostream>
#include <algorithm>    // std::min_element, std::max_element
#include <math.h>       /* floor */

#include "pointd.hpp"
#include "color_obj.hpp"

#include "window.hpp"

struct game_obj_velocity {
	double angle;
	double velocity;
};

struct game_obj_box {
	int x_max; // maximum horizontal value of component
	int y_max; // maximum vertcal value of component
	int x_min; // minimum horizontal value of component
	int y_min; // minimum vertcal value of component
};

class game_obj
{
public:
	game_obj(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, bool _on_off);

	~game_obj() = default; // double check with the experts whether i need to write deconstructor and how for mutiple asteroids in a vector

private:
	// has the obect moved off the screen, if so wrap around
	void check_boundaries() const;

public:
	virtual void draw() const;

	// adjust size of all the main game elments to make realstic looking game
// use of template allows for object and scale to be used together, othwise get type incompatible error
	template<typename T, std::size_t vertex_num>
	void scale_game_object_data(T(&object_ref_data)[vertex_num], const double scale) {
		for (int j = 0; j < vertex_num; ++j) {
			object_ref_data[j].x *= scale;
			object_ref_data[j].y *= scale;
		}
	}

	// random numbers
	double rand_angle() const;

	int rand_saucer_start_y() const;

	double rand_nudge_angle() const;

	// obvious
	void move();

	// game object collisions
	bool collider(const SDL_Point &point) const;

	// set up the centre of an object explosion and define shrapnel stars
	void obj_explosion_set(const pointd & original_obj_centre);

	// maintain explosion until stars reach a cerain radius
	void obj_explosion();

	// thickness object render lines (TBD)
	void thick_line();

	int num_pts{};
	SDL_Point *vertices;
	//SDL_Point *vertices_line_above; 
	//SDL_Point *vertices_line_below;
	SDL_Point position;
	game_obj_velocity av;
	bool on_off{ false };
	pointd obj_centre{ 0.0,0.0 };
	bool explode{ false };
	int explode_radius{ 0 };
	int	explosion_size{ 32 };
	pointd explode_centre{ 0, 0 };

private:
	double fabs_x{};
	double fabs_y{};
	double xf{};
	double yf{};
	pointd ship_inc_pos{ 1.0,1.0 };
	game_obj_box game_obj_box{ 0,0,0,0 };
	int num_shrapnel{ 12 };
	SDL_Point explosion_stars[12]{
		{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}
	};
};
