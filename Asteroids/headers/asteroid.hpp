#pragma once

#include <iostream>

class asteroid : public game_obj
{
public:
	asteroid() = default;
	asteroid(SDL_Point *_vertices, const int &_num_pts, SDL_Point _position, game_obj_velocity _av, bool _on_off, char _type, const int &_score) :
		game_obj(_vertices, _num_pts, _position, _av, _on_off),
		type{ _type },
		score{ _score }
	{}
	~asteroid() = default;

	void asteroid_split(const bool rock_ID, const pointd &original_rock_centre) {
//		std::cout << "Split Asteroid!!\n";
		int asteroid_shape_reference_index = rand() % ROCK_TYPE_COUNT;
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
		rock_ID ? av.angle = av.angle + PI / 4 : av.angle = av.angle - PI / 4;
		obj_explosion_set(original_rock_centre);
	}

	bool proxmity_to_centre_of_screen() {
		bool close{ false };
		for (int k = 0; k < num_pts; ++k) {
			if (abs(vertices[k].x - window_X / 2.0) < 50) close = true;
			if (abs(vertices[k].y - window_Y / 2.0) < 50) close = true;
		}
		return close;
	}

	char type{};
	int score{ 0 };
};

