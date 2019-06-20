#include "enemy_ship.hpp"

#include "big_enemy_ship_data.hpp"
#include "small_enemy_ship_data.hpp"

constexpr auto PI = 3.14159265359;

int enemy_ship::delay = ENEMY_SHIP_FIRE_DELAY; 
int const enemy_ship::fire_border{ SMALL_ENEMY_SHIP_FIRE_BORDER };

enemy_ship::enemy_ship(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, bool _on_off, const int &_score, const double &_scale)
	:
	game_obj(_vertices, _num_pts, _position, _av, _on_off),
	score{ _score },
	scale{ _scale }
{
	scale_game_object_data(big_enemy_ship_ref, SCALE_BIG_ENEMY_SHIP);
	scale_game_object_data(small_enemy_ship_ref, SCALE_SMALL_ENEMY_SHIP);
}

void enemy_ship::check_launch_enemy_ship() {
	if (!on_off) {
		on_off = true;
		av.angle = rand_angle();
		y = rand_saucer_start_y();
		y < 100 ? y += 50 : y;
		x = -20 - vertices[0].x; // make sure saucer starts transit off screen
		if (av.angle > PI / 2.0 && av.angle < 3.0*PI / 2.0) {
			x = window_X + 20 + -vertices[0].x;
		}
		for (int i = 0; i < num_pts; ++i) {
			vertices[i].x += x;
			vertices[i].y += y;
		}
	}
}

void enemy_ship::destroy_enemy_ship(const Uint32 &current_start_time) {
	on_off = false;
	start_time = current_start_time;
	for (int i = 0; i < num_pts; ++i) {
		vertices[i].x -= 1000;
		vertices[i].y -= 1000;
	}
}

bool enemy_ship::check_enemy_ship_bullet_hit(player_bullet_list &bullets, const Uint32 &current_start_time) {
	for (int j = 0; j < num_pts; ++j) {
		for (int j = 0; j < bullets.list.size(); ++j) {
			if (collider({ static_cast <int>(bullets.list[j].position.x), static_cast <int> (bullets.list[j].position.y) })) {
				destroy_enemy_ship(current_start_time);
				obj_explosion_set(obj_centre);
				bullets.list[j].on_off = false;
				bullets.list[j].position = { -200, -200 };
				return true;
			}
		}
	}
	return false;
}

big_enemy_ship_construct::big_enemy_ship_construct() {
	visit_interval = BIG_ENEMY_SHIP_TIMING;
};
enemy_ship big_enemy_ship_construct::ship(big_enemy_ship_ref, BIG_ENEMY_SHIP_VERTEX_COUNT, intial_position_big_enemy_ship, initial_velocity_big_enemy_ship, show_big_enemy_ship, BIG_ENEMY_SHIP_SCORE, SCALE_BIG_ENEMY_SHIP);

small_enemy_ship_construct::small_enemy_ship_construct() {
	visit_interval = SMALL_ENEMY_SHIP_TIMING;
};
enemy_ship small_enemy_ship_construct::ship(small_enemy_ship_ref, SMALL_ENEMY_SHIP_VERTEX_COUNT, intial_position_small_enemy_ship, initial_velocity_small_enemy_ship, show_small_enemy_ship, SMALL_ENEMY_SHIP_SCORE, SCALE_SMALL_ENEMY_SHIP);