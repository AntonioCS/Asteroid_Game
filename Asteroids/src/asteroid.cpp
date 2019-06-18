#include "asteroid.hpp"
#include <algorithm>

#include "big_asteroid_data.hpp"
#include "medium_asteroid_data.hpp"
#include "small_asteroid_data.hpp"

int const asteroid::start_count{ BIG_ROCK_START_COUNT };
int const asteroid::num_of_big_rock{ BIG_ROCK_COUNT };
int const asteroid::num_of_medium_rock{ MEDIUM_ROCK_COUNT };
int const asteroid::total_rocks = { BIG_ROCK_COUNT + MEDIUM_ROCK_COUNT + SMALL_ROCK_COUNT };

asteroid::asteroid(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, bool _on_off, const char &_type, const int &_score) :
	game_obj(_vertices, _num_pts, _position, _av, _on_off),
	type{ _type },
	score{ _score }
{}

void asteroid::asteroid_split(const bool rock_ID, const pointd &original_rock_centre, const double &old_asteroid_angle) {
	//		std::cout << "Split Asteroid!!\n";
	int asteroid_shape_reference_index = rand() % 4;
	if (type == 'm') {
		//			std::cout << asteroid_shape_reference_index << " big rock bullet hit \n";
		for (int k = 0; k < num_pts; ++k) {
			vertices[k].x = original_rock_centre.x + medium_rocks_ref[asteroid_shape_reference_index][k].x;
			vertices[k].y = original_rock_centre.y + medium_rocks_ref[asteroid_shape_reference_index][k].y;
		}
	}
	else if (type == 's') {
		//			std::cout << "medium rock bullet hit\n";
		for (int k = 0; k < num_pts; ++k) {
			vertices[k].x = original_rock_centre.x + small_rocks_ref[asteroid_shape_reference_index][k].x;
			vertices[k].y = original_rock_centre.y + small_rocks_ref[asteroid_shape_reference_index][k].y;
		}
	}
	on_off = true;
	rock_ID ? av.angle = old_asteroid_angle + (PI / 2.0) * rand_nudge_angle() : av.angle = old_asteroid_angle - (PI / 2.0) * rand_nudge_angle();
	obj_explosion_set(original_rock_centre);
}

bool asteroid::proxmity_to_centre_of_screen() {
	bool close{ false };
	for (int k = 0; k < num_pts; ++k) {
		if (abs(vertices[k].x - window_X / 2.0) < window_X / 30.0) close = true;
		if (abs(vertices[k].y - window_Y / 2.0) < window_Y / 30.0) close = true;
	}
	return close;
}

all_asteroids::all_asteroids() {
	scale_game_object_data(big_rocks_ref, SCALE_BIG_ROCK);
	scale_game_object_data(medium_rocks_ref, SCALE_MEDIUM_ROCK);
	scale_game_object_data(small_rocks_ref, SCALE_SMALL_ROCK);
	int index = 0;
	for (int i = 0; i < 84; ++i) {
		for (int j = 0; j < 12; ++j) {
			if (i < 12) { rocks[i][j] = big_rocks_ref[index][j]; }
			else if (i >= 12 && i < 36) { rocks[i][j] = medium_rocks_ref[index][j]; }
			else { rocks[i][j] = small_rocks_ref[index][j]; }
		};
		index > (4 - 2) ? index = 0 : index++;
	}
	for (int i = 0; i < 12; ++i) {
		asteroid asteroid(rocks[i], BIG_ROCK_VERTEX_COUNT, intial_position_big_rocks[i], initial_velocity_big_rocks[i], show_big_rocks[i], BIG_ROCK, 20);
		list.push_back(asteroid);
	}
	for (int i = 12; i < 36; ++i) {
		asteroid asteroid(rocks[i], MEDIUM_ROCK_VERTEX_COUNT, intial_position_medium_rocks[i - 12], initial_velocity_medium_rocks[i - 12], show_medium_rocks[i - 12], MEDIUM_ROCK, 50);
		list.push_back(asteroid);
	}
	for (int i = 36; i < 84; ++i) {
		asteroid asteroid(rocks[i], SMALL_ROCK_VERTEX_COUNT, intial_position_small_rocks[i - 36], initial_velocity_small_rocks[i - 36], show_small_rocks[i - 36], SMALL_ROCK, 100);
		list.push_back(asteroid);
	}
};

void all_asteroids::reset(const std::vector<SDL_Point> &original) {
	for (auto i = 0; i < 12; ++i) {
		for (auto j = 0; j < 12; ++j) {
			list[i].vertices[j].x = original[i * 12 + j].x;
			list[i].vertices[j].y = original[i * 12 + j].y;
		}
	}
}






