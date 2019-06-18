#pragma once

#include <iostream>
#include <vector>

#include "_game_obj.hpp"

class asteroid : public game_obj
{
public:
	asteroid() = default;
	asteroid(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, bool _on_off, const char &_type, const int &_score);
	~asteroid() = default;

	void asteroid_split(const bool rock_ID, const pointd &original_rock_centre, const double &old_asteroid_angle);
	bool proxmity_to_centre_of_screen();

	char type{};
	int score{};
	static const int start_count;
	static const int num_of_big_rock;
	static const int num_of_medium_rock;
	static const int total_rocks;
};

class all_asteroids {
public:
	all_asteroids();
	~all_asteroids() = default;

	void reset(const std::vector<SDL_Point> &original);

	template<typename T, std::size_t type_num, std::size_t vertex_num>
	void scale_game_object_data(T(&object_ref_data)[type_num][vertex_num], const double scale) {
		for (int i = 0; i < type_num; ++i) {
			for (int j = 0; j < vertex_num; ++j) {
				object_ref_data[i][j].x *= scale;
				object_ref_data[i][j].y *= scale;
			}
		}
	}

	std::vector<asteroid> list;
};


