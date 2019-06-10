#pragma once

#include <iostream>

class enemy_ship : public game_obj
{
public:
	enemy_ship(SDL_Point *_vertices, const int &_num_pts, SDL_Point _position, game_obj_velocity _av, bool _on_off, int _score)
		:
		game_obj(_vertices, _num_pts, _position, _av, _on_off),
		score{ _score }
	{}
	~enemy_ship() = default;

	// launch enemy ship from either side of the screeen at a random angle
	void check_launch_enemy_ship() {
		if (!on_off) {
			on_off = true;
			av.angle = PIx2_RAND(gen);
			y = window_Y_RAND(gen);
			x = -20 - vertices[0].x;
			if (av.angle > PI / 2.0 && av.angle < 3.0*PI / 2.0) {
				x = window_X + 20 + -vertices[0].x;
			}
			for (int i = 0; i < num_pts; ++i) {
				vertices[i].x += x;
				vertices[i].y += y;
			}
		}
	}

	void destroy_enemy_ship(const Uint32 &current_start_time) {
		on_off = false;
		start_time = current_start_time;
		for (int i = 0; i < num_pts; ++i) {
			vertices[i].x -= 1000;
			vertices[i].y -= 1000;
		}
	}

	bool check_enemy_ship_bullet_hit(std::vector<bullet> &bullet_list, const Uint32 &current_start_time) {
		for (int j = 0; j < num_pts; ++j) {
			for (int j = 0; j < bullet_list.size(); ++j) {
				if (collider({ static_cast <int>(bullet_list[j].position.x), static_cast <int> (bullet_list[j].position.y) })) {
					destroy_enemy_ship(current_start_time);
					obj_explosion_set(obj_centre);
					bullet_list[j].on_off = false;
					bullet_list[j].position = { BULLET_POS_OFF_SCREEN, BULLET_POS_OFF_SCREEN };
					return true;
				}
			}
		}
		return false;
	}

	int score{ 0 };
	Uint32 start_time{0};

private:
	int x{ 0 };
	int y{ 0 };
};

	
