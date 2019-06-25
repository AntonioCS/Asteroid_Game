#include <iostream>
#include <math.h>       /* ceil */
#include <vector>
#include <array>
//#include <stdlib.h>     /* srand, rand */
#include <sstream>

#include "window.hpp"
#include "_game_obj.hpp"
#include "big_asteroid_data.hpp"
#include "medium_asteroid_data.hpp"
#include "small_asteroid_data.hpp"
#include "common_asteroid_data.hpp"
#include "player_ship_data.hpp"
#include "bullet_data.hpp"
#include "asteroid.hpp"
#include "player_ship.hpp"
#include "bullet.hpp"
#include "control.hpp"
#include "asteroid_set.hpp"


void poll_all_events(window &window, const Uint8 *keystate) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		window.x_close_chk(event);
	}
	window.poll_events(keystate);
}

int main(int argc, char *argv[]) {

	window asteroid_window("Asteroids", window_X, window_Y);

	std::vector<asteroid> big_asteroid_list = initialise_big_rocks();
	std::vector<asteroid> medium_asteroid_list = initialise_medium_rocks();
	std::vector<asteroid> small_asteroid_list = initialise_small_rocks();

	std::vector<asteroid> all_asteroids = initialise_rocks();

	std::vector<bullet> bullet_list;
	for (int i = 0; i < NUM_BULLETS; ++i) {
		bullet bullet;
		bullet_list.push_back(bullet);
	}

	player_ship ship(player_space_ship, PLAYER_SHIP_VERTEX_COUNT, intial_position_ship, initial_velocity_ship);

	//	score score2(window::renderer, "D:/CPP_Games/Asteroids/Asteroids/data/bit5x5.ttf", font_size, std::to_string(ball.score_p2), player_color);
	const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
	//Current time start time
	bool space_key_release{ false }, big_rock_just_split{ false }, med_rock_just_split = false;;
	int c1{ 0 }; // debug variable
	int c2{ 0 }; // debug variable
	int asteroid_shape_reference_index{ 0 }; // asteroid shape reference index number


	Uint32 start_time = 0;
	Uint32 end_time = 0;
	int count{ 0 };

	int screen_refresh_rate = 1000 / asteroid_window.get_refresh_rate();
	std::cout << "Screen Refresh Rate = " << screen_refresh_rate << "\n";

	while (!asteroid_window.is_closed()) {
		start_time = SDL_GetTicks();
		//	std::cout << start_time << ", " << end_time << "\n";
		if (start_time > end_time + screen_refresh_rate) {
			end_time = start_time;
			big_rock_just_split = false;
			med_rock_just_split = false;
			SDL_PumpEvents();
			poll_all_events(asteroid_window, keystate);

			for (int i = 0; i < BIG_ROCK_COUNT; ++i) {
				if (big_asteroid_list[i].on_off) {
					big_asteroid_list[i].move();
					big_asteroid_list[i].draw();
					for (int j = 0; j < NUM_BULLETS; ++j) {
						if (big_asteroid_list[i].collider({ static_cast <int>(bullet_list[j].position.x), static_cast <int> (bullet_list[j].position.y) })) {
							big_asteroid_list[i].on_off = false;
							bullet_list[j].on_off = false;
							bullet_list[j].position = { -100, -100 };
							medium_asteroid_list[i * 2 + 1].asteroid_split(big_asteroid_list[i].obj_centre, big_asteroid_list[i].av.angle, i * 2 + 1, 'm');
							medium_asteroid_list[i * 2].asteroid_split(big_asteroid_list[i].obj_centre, big_asteroid_list[i].av.angle, i * 2, 'm');
							big_rock_just_split = true;
						}
					}
					for (int j = 0; j < PLAYER_SHIP_VERTEX_COUNT; ++j) {
						if (big_asteroid_list[i].collider({ ship.vertices[j].x, ship.vertices[j].y })) {
						}
					}
				}
			}
			for (int i = 0; i < MEDIUM_ROCK_COUNT; ++i) { // combine big and small rocks into single intialiser
				if (medium_asteroid_list[i].on_off && !big_rock_just_split) {
					medium_asteroid_list[i].move();
					medium_asteroid_list[i].draw();
					for (int j = 0; j < NUM_BULLETS; ++j) {
						if (medium_asteroid_list[i].collider({ static_cast <int>(bullet_list[j].position.x), static_cast <int> (bullet_list[j].position.y) })) {
							medium_asteroid_list[i].on_off = false;
							bullet_list[j].on_off = false;
							bullet_list[j].position = { -100, -100 };
							small_asteroid_list[i * 2 + 1].asteroid_split(medium_asteroid_list[i].obj_centre, medium_asteroid_list[i].av.angle, i * 2 + 1, 's');
							small_asteroid_list[i * 2].asteroid_split(medium_asteroid_list[i].obj_centre, medium_asteroid_list[i].av.angle, i * 2, 's');


							med_rock_just_split = true;
						}
					}
					for (int j = 0; j < PLAYER_SHIP_VERTEX_COUNT; ++j) {
						if (medium_asteroid_list[i].collider({ ship.vertices[j].x, ship.vertices[j].y })) {
						}
					}
				}
			}

			for (int i = 0; i < SMALL_ROCK_COUNT; ++i) { // combine big and small rocks into single intialiser
				if (small_asteroid_list[i].on_off && !big_rock_just_split && !med_rock_just_split) {
					small_asteroid_list[i].move();
					small_asteroid_list[i].draw();
					for (int j = 0; j < NUM_BULLETS; ++j) {
						if (small_asteroid_list[i].collider({ static_cast <int>(bullet_list[j].position.x), static_cast <int> (bullet_list[j].position.y) })) {
							small_asteroid_list[i].on_off = false;
							bullet_list[j].on_off = false;
							bullet_list[j].position = { -100, -100 };
						}
					}
					for (int j = 0; j < PLAYER_SHIP_VERTEX_COUNT; ++j) {
						if (small_asteroid_list[i].collider({ ship.vertices[j].x, ship.vertices[j].y })) {
						}
					}
				}
			}


			for (int i = 0; i < NUM_BULLETS; ++i) {
				if (bullet_list[i].on_off) {
					bullet_list[i].move();
					bullet_list[i].draw();
				}
			}

			//		std::cout <<"ship vel "<< ship.av.velocity << "\n";
			ship.move();
			// draw ship
			ship.draw();
			// move ship
			//ship.av.velocity /= ship.drag; // velocity decay

			if (keystate[SDL_SCANCODE_LEFT]) { ship.rotate_left(); }
			if (keystate[SDL_SCANCODE_RIGHT]) { ship.rotate_right(); }
			if (keystate[SDL_SCANCODE_UP]) { ship.thrust(); }
			if (keystate[SDL_SCANCODE_Z]) { ship.hyperspace(); }
			if (keystate[SDL_SCANCODE_SPACE] && space_key_release) {
				space_key_release = false;
				for (auto i = 0; i < NUM_BULLETS; ++i) {
					if (!bullet_list[i].on_off) {
						bullet_list[i].fire(ship.vertices[0], ship.ship_orientation);
						break;
					}
				}
			}
			if (!keystate[SDL_SCANCODE_SPACE]) space_key_release = true;
			asteroid_window.clear();
		}
	}

	return 0;
}


