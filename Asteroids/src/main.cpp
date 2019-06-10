#include <iostream>
#include <math.h>       /* ceil */
#include <algorithm>    /* std::min */
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <iterator>
#include <random>

#include "window.hpp"
#include "_game_obj.hpp"
#include "random_num.hpp"
#include "big_asteroid_data.hpp"
#include "medium_asteroid_data.hpp"
#include "small_asteroid_data.hpp"
#include "misc_data.hpp"
#include "player_ship_data.hpp"
#include "bullet_data.hpp"
#include "big_enemy_ship_data.hpp"
#include "small_enemy_ship_data.hpp"

#include "asteroid.hpp"
#include "bullet.hpp"
#include "player_ship.hpp"
#include "enemy_ship.hpp"
#include "game_control.hpp"
#include "show_score.hpp"
#include "show_message.hpp"
#include "show_remain_lives.hpp"
#include "set_up.hpp"


int main(int argc, char *argv[]) {

	scale_all_game_objects();

	window asteroid_window("Asteroids", window_X, window_Y);
	
	std::vector<asteroid> all_asteroids = initialise_rocks(); // build the array of all the rocks used in the game

	std::vector<bullet> bullet_list = make_bullets(NUM_BULLETS, PLAYER_BULLET_SPEED);
	std::vector<bullet> enemy_bullet_list = make_bullets(NUM_ENEMY_BULLETS_SMALL_SHIP, ENEMY_BULLET_SPEED);

	std::vector<show_remain_lives> show_remain_lives_list = remaining_lives();

	player_ship ship(player_space_ship_ref, TOTAL_SHIP_VERTEX_COUNT, intial_position_ship, initial_velocity_ship);

	enemy_ship big_enemy_ship(big_enemy_ship_ref, BIG_ENEMY_SHIP_VERTEX_COUNT, intial_position_big_enemy_ship, initial_velocity_big_enemy_ship, show_big_enemy_ship, BIG_ENEMY_SHIP_SCORE);

	enemy_ship small_enemy_ship(small_enemy_ship_ref, SMALL_ENEMY_SHIP_VERTEX_COUNT, intial_position_small_enemy_ship, initial_velocity_small_enemy_ship, show_small_enemy_ship, SMALL_ENEMY_SHIP_SCORE);

	text_message title_message(window::renderer, msg.font, msg.game_message_font_size, "©1979 ATARI INC", player_color);
	text_message game_over(window::renderer, msg.font, msg.score_font_size, "GAME OVER", player_color);
	text_message level_num(window::renderer, msg.font, msg.score_font_size, "NEW LEVEL", player_color);

	score score(window::renderer, msg.font, msg.score_font_size, std::to_string(ship.player_score), player_color);

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	
	control game;
	bool asteroid_too_close_to_reset_position{ false };

	int screen_refresh_rate = asteroid_window.get_refresh_rate(); // every xx of a second

	// **** MAIN GAME LOOP ****

	while (!asteroid_window.is_closed()) {

		// Make sure Game run at the correct screen refresh Rate, asumed 60Hz for game speed
		game.start_time = SDL_GetTicks();
		if (game.start_time > game.end_time + screen_refresh_rate) {
			game.end_time = game.start_time;

		// Clear keyboard buffer and get new keyboard sample
			SDL_PumpEvents();
			asteroid_window.poll_all_events(keystate);

		// Does the player get another ship
			if (ship.player_score > ship.extra_ship ) {
				++ship.lives; 
				ship.extra_ship	+= 10000;
			}
			ship.lives = std::min(SHOW_LIVES_COUNT, ship.lives);

		// Display scoe and Atari title
			score.display(100, 60, window::renderer, std::to_string(ship.player_score), msg.score_font_size);
			title_message.display(340, 550, window::renderer);

			asteroid_too_close_to_reset_position = false; // reset ateroid reposition flag

		// Check for an asteroid hit by player bullets
			for (int i = 0; i < TOTAL_ROCKS; ++i) {
				if (all_asteroids[i].on_off) { // only check active rocks
					game.one_left = true; // the screen isn't empty of rocks
					all_asteroids[i].move();
					all_asteroids[i].draw();
					// check whether any player bullets have hit an asteroid
					for (int j = 0; j < NUM_BULLETS; ++j) {
						if (all_asteroids[i].collider({ static_cast <int>(bullet_list[j].position.x), static_cast <int> (bullet_list[j].position.y) }) && ship.on_off) {
							all_asteroids[i].on_off = false;
							bullet_list[j].on_off = false;
							bullet_list[j].position = { -100, -100 };
							ship.player_score += all_asteroids[i].score;
							// if a big asteroid is hit then spllit it into two medium ones
							if (all_asteroids[i].type == 'b') {
								all_asteroids[BIG_ROCK_COUNT + i * 2 + 1].asteroid_split(1, all_asteroids[i].obj_centre);
								all_asteroids[BIG_ROCK_COUNT + i * 2].asteroid_split(0, all_asteroids[i].obj_centre);
							}
							// if a medium asteroid is hit then spllit it into two small ones
							else if (all_asteroids[i].type == 'm') {
								all_asteroids[BIG_ROCK_COUNT + MEDIUM_ROCK_COUNT + i * 2 + 1].asteroid_split(1, all_asteroids[i].obj_centre);
								all_asteroids[BIG_ROCK_COUNT + MEDIUM_ROCK_COUNT + i * 2].asteroid_split(0, all_asteroids[i].obj_centre);
							}
							//otherwise if a small asteroid is hit then blow it up
							else if (all_asteroids[i].type == 's') {
								std::cout << "small hit!\n";
								all_asteroids[i].obj_explosion_set(all_asteroids[i].obj_centre);
							}
						}
					}
					// check whether the current asteroid under exmamination is close to screen centre
					if (all_asteroids[i].proxmity_to_centre_of_screen()) asteroid_too_close_to_reset_position = true;

					// has an asteroid hit the player ship?
					for (int j = 0; j < PLAYER_SHIP_VERTEX_COUNT; ++j) {
						if (all_asteroids[i].collider({ ship.vertices[j].x, ship.vertices[j].y }) && ship.on_off) {
							ship.got_hit(); 
						}
					}
				}
				// if the asteroid has been hit then keep explosion going until finished
				all_asteroids[i].obj_explosion();
			}

			// if the ship has been destroyed, the ships explosion has finished and there's no asteroid really close to the centre of the screen then the player ship can be reset
			if(!ship.on_off && !asteroid_too_close_to_reset_position && !ship.explode) { ship.reset_pos(); }
			
			// check whether the big saucer has hit the player
			for (int j = 0; j < PLAYER_SHIP_VERTEX_COUNT; ++j) {
				if (big_enemy_ship.collider({ ship.vertices[j].x, ship.vertices[j].y }) && ship.on_off) {
				//	std::cout <<"big saucer hit player ship\n";
					big_enemy_ship.destroy_enemy_ship(game.start_time);
					ship.got_hit();
				}
			}

			// check whether the small saucer has hit the player
			for (int j = 0; j < PLAYER_SHIP_VERTEX_COUNT; ++j) {
				if (small_enemy_ship.collider({ ship.vertices[j].x, ship.vertices[j].y }) && ship.on_off) {
				//	std::cout << "small saucer hit player ship\n";
					--ship.lives;
					small_enemy_ship.destroy_enemy_ship(game.start_time);
					ship.got_hit();
					
				}
			}

			// check whether the small saucer has shot the player
			for (int i = 0; i < NUM_ENEMY_BULLETS_SMALL_SHIP; ++i) {
				if (ship.collider({ static_cast <int>(enemy_bullet_list[i].position.x), static_cast <int>(enemy_bullet_list[i].position.y) }) && ship.on_off)	{
				//	std::cout << "small saucer shot player ship\n";
				ship.got_hit();
				}
			}
			
			// if the player has been hit then keep explosion going until finished 
			if (ship.explode) ship.explode_player_ship();

			// Has the player lost his last life?
			if (ship.lives < 1) {
				game_over.display(GAME_OVER_MSG.x, GAME_OVER_MSG.y, window::renderer);
				ship.on_off = false;
			}

			if (ship.on_off) {
				ship.move();
				ship.draw();
			}

			// check timing interval and launch big saucer when required and then check for player bullet impacts as it flys around screen
			if (game.start_time > big_enemy_ship.start_time + BIG_ENEMY_SHIP_TIMING) {
				big_enemy_ship.check_launch_enemy_ship();
			}
			if (big_enemy_ship.on_off) {
				if (big_enemy_ship.check_enemy_ship_bullet_hit(bullet_list, game.start_time)) {
				//	std::cout << "big saucer hit!\n";
					ship.player_score += big_enemy_ship.score;
				};
				big_enemy_ship.move();
				big_enemy_ship.draw();
			}
			// if the big saucer has been hit then keep explosion going until finished 
			big_enemy_ship.obj_explosion();

			// check timing interval and launch small saucer when required and then check for player bullet impacts as it flys around screen
			if (game.start_time > small_enemy_ship.start_time + SMALL_ENEMY_SHIP_TIMING) {
				small_enemy_ship.check_launch_enemy_ship();
			}
			if (small_enemy_ship.on_off) {
				if (small_enemy_ship.check_enemy_ship_bullet_hit(bullet_list, game.start_time)) {
				//	std::cout << "small saucer hit!\n";
					ship.player_score += small_enemy_ship.score;
					std::for_each(enemy_bullet_list.begin(), enemy_bullet_list.end(), [](bullet &bullet) {
						bullet.on_off = false;
					});
				};

				small_enemy_ship.move();
				small_enemy_ship.draw();
				// move small saucer bullets 
				std::for_each(enemy_bullet_list.begin(), enemy_bullet_list.end(), [](bullet &bullet) {
					++bullet.delay;
					if (bullet.on_off) {
						bullet.move();
						bullet.draw();
					} 
				});
			}
			// keep small saucer explosion going as required
			small_enemy_ship.obj_explosion();

			// don't fire any small saucer bullets until well inside screen border. Distrbute bullets in a random polar coordinate pattern. fire from small ship vertex 0 arbitary
			if (small_enemy_ship.obj_centre.x > SMALL_ENEMY_SHIP_FIRE_BORDER && small_enemy_ship.obj_centre.x < window_X - SMALL_ENEMY_SHIP_FIRE_BORDER) {
				std::for_each(enemy_bullet_list.begin(), enemy_bullet_list.end(), [&](bullet &bullet) {
					if (!bullet.on_off && bullet.delay > ENEMY_FIRE_DELAY) {
						bullet.fire(small_enemy_ship.vertices[0], PIx2_RAND(gen));
					}
				});
			}

			// move player bullets if fired
			std::for_each(bullet_list.begin(), bullet_list.end(), [](bullet &bullet) {
				if (bullet.on_off) {
					bullet.move();
					bullet.draw();
				}
			});
			
			// show remaining lives as triangles under score. reset remaining lives list to match number of lives of player ship and then draw each one
			for (int i = 0; i < SHOW_LIVES_COUNT; ++i) {
				show_remain_lives_list[i].on_off = false;
				if (i < ship.lives) { show_remain_lives_list[i].on_off = true; }
			}
			std::for_each(show_remain_lives_list.begin(), show_remain_lives_list.end(), [](show_remain_lives &life) {
				if (life.on_off) {
					life.draw();
				}
			});

			// if we're playing the game then sample ship controls and respond accordingly
			if (ship.on_off) {
				if (keystate[SDL_SCANCODE_LEFT]) { ship.rotate_left(); }
				if (keystate[SDL_SCANCODE_RIGHT]) { ship.rotate_right(); }
				if (keystate[SDL_SCANCODE_UP]) { ship.thrust(); ship.show_thrust = true; }
				if (!keystate[SDL_SCANCODE_UP]) { ship.show_thrust = false; }
				if (keystate[SDL_SCANCODE_Z]) { ship.hyperspace(); }

				if (keystate[SDL_SCANCODE_SPACE] && asteroid_window.space_key_release) {
					asteroid_window.space_key_release = false;
					for (auto i = 0; i < NUM_BULLETS; ++i) {
						if (!bullet_list[i].on_off) {
							bullet_list[i].fire(ship.vertices[0], ship.ship_orientation);
							break;
						}
					}
				}
			}
			// make sur eplyer has to pres space everytime they want to fire a bullet, no automaticl firing
			if (!keystate[SDL_SCANCODE_SPACE]) asteroid_window.space_key_release = true;

			// shot all the rocks, go up a level, increase the number of initial big asteroids and start again
			if (!game.one_left) {
				++game.level;
				all_asteroids = initialise_rocks();
				game.level = std::min(BIG_ROCK_COUNT, game.level);
				game.level_start_time = SDL_GetTicks();
				for (int i = 0; i < game.level + BIG_ROCK_START_COUNT; ++i) {
					all_asteroids[i].on_off = true;
				}
				ship.reset_pos(); //if we reset all rocks to start and player to middle of screen then dont need to check for collisions
			}
			else { game.one_left = false; }

			asteroid_window.clear();
		}
	}

	return 0;
}


