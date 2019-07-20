#include <iostream>
#include <math.h>       /* ceil */
#include <algorithm>    /* std::min */
#include <vector>
#include <array>
#include <string>
#include <iterator>

#include "window.hpp"
#include "sounds.hpp"
#include "game_control.hpp"
#include "msg.hpp"

#include "_game_obj.hpp"

#include "asteroid.hpp"
#include "bullet.hpp"
#include "player_ship.hpp"
#include "enemy_ship.hpp"

#include "show_score.hpp"
#include "show_message.hpp"
#include "show_remain_lives.hpp"
#include "high_score.hpp"

int main(int argc, char *argv[]) {

	SDL_Color player_color;
	window asteroid_window("Asteroids", window_X, window_Y);
	
	all_asteroids all_asteroids_active; // build a dynamic array to show all rocks during the game
	std::vector<SDL_Point> original;  // copy dynamic array and store all original positions etc.. for gam / level reset / restart
	
	for (auto i = 0; i < 84; ++i) {
		for (auto j = 0; j < 12; ++j) {
			original.push_back({ all_asteroids_active.list[i].vertices[j].x, all_asteroids_active.list[i].vertices[j].y });
		}
	}

	high_score high_score;

	sounds sounds;
	
	player_bullet_list player_bullets;

	enemy_bullet_list enemy_bullets;

	remaining_lives remaining_lives;

	ship_construct player;

	big_enemy_ship_construct big_enemy;

	small_enemy_ship_construct small_enemy;

	msg msg; // ref struct to set message font and size

	text_message title_message(window::renderer, msg.font, msg.game_message_font_size, "©1979 ATARI INC", player_color);
	text_message game_over(window::renderer, msg.font, msg.score_font_size, "GAME OVER", player_color);
	text_message restart(window::renderer, msg.font, msg.score_font_size, "Press 'R' to restart a new game", player_color);
	text_message level_num(window::renderer, msg.font, msg.score_font_size, "NEW LEVEL", player_color);
	text_message high_score_title(window::renderer, msg.font, msg.score_font_size, "HIGH SCORES", player_color);

	score score(window::renderer, msg.font, msg.score_font_size, std::to_string(player.ship.score), player_color);

	control game;
	
	game.screen_refresh_rate = asteroid_window.get_refresh_rate(); // every xx of a second

	// **** MAIN GAME LOOP ****
	while (!asteroid_window.is_closed()) {
		
		// Make sure Game run at the correct screen refresh Rate, asumed 60Hz for game speed
		game.start_time = SDL_GetTicks();
		if (game.start_time >= game.end_time + game.screen_refresh_rate) {
			game.end_time = game.start_time;

			sounds.beat_count > 50 ? Mix_PlayChannel(-1, sounds.game_heart_beat, 0), sounds.beat_count = 0 : ++sounds.beat_count;

			// Clear keyboard buffer and get new keyboard sample
			//SDL_PumpEvents();
			asteroid_window.poll_all_events(game.keystate);

			if (player.ship.earn_life()) Mix_PlayChannel(-1, sounds.extra_ship, 0);

			// Display score and Atari title
			score.display(window_X / 8, window_Y / 10, window::renderer, std::to_string(player.ship.score), msg.score_font_size);
			title_message.display(window_X / 2.5, window_Y / 1.2, window::renderer);

			game.asteroid_too_close_to_reset_position = false; // reset ateroid reposition flag

		// Check for an asteroid hit by player bullets
			for (auto i = 0; i < all_asteroids_active.list[0].total_rocks; ++i) {
				if (all_asteroids_active.list[i].on_off) { // only check active rocks
					game.one_left = true; // the screen isn't empty of rocks
					all_asteroids_active.list[i].move();
					all_asteroids_active.list[i].draw();
					// check whether any player bullets have hit an asteroid, loop through asteroids and each bullet for collisions
					for (auto j = 0; j < player_bullets.list.size(); ++j) {
						if (all_asteroids_active.list[i].collider({ static_cast <int>(player_bullets.list[j].position.x), static_cast <int> (player_bullets.list[j].position.y) }) && player.ship.on_off) {
							all_asteroids_active.list[i].on_off = false;
							player_bullets.list[j].on_off = false;
							player_bullets.list[j].position = player_bullets.list[j].off_position;
							player.ship.score += all_asteroids_active.list[i].score;
							// if a big asteroid is hit then spllit it into two medium ones
							if (all_asteroids_active.list[i].type == 'b') {
								Mix_PlayChannel(-1, sounds.explode_big_asteroid, 0);
								all_asteroids_active.list[all_asteroids_active.list[0].num_of_big_rock + i * 2 + 1].asteroid_split(1, all_asteroids_active.list[i].obj_centre, all_asteroids_active.list[i].av.angle);
								all_asteroids_active.list[all_asteroids_active.list[0].num_of_big_rock + i * 2].asteroid_split(0, all_asteroids_active.list[i].obj_centre, all_asteroids_active.list[i].av.angle);

							}
							// if a medium asteroid is hit then spllit it into two small ones
							else if (all_asteroids_active.list[i].type == 'm') {
								Mix_PlayChannel(-1, sounds.explode_medium_asteroid, 0);
								all_asteroids_active.list[all_asteroids_active.list[0].num_of_big_rock + i * 2 + 1].asteroid_split(1, all_asteroids_active.list[i].obj_centre, i);
								all_asteroids_active.list[all_asteroids_active.list[0].num_of_big_rock + i * 2].asteroid_split(0, all_asteroids_active.list[i].obj_centre, i);
							}
							//otherwise if a small asteroid is hit then blow it up
							else if (all_asteroids_active.list[i].type == 's') {
								Mix_PlayChannel(-1, sounds.explode_small_asteroid, 0);
								//std::cout << "small hit!\n";
								all_asteroids_active.list[i].obj_explosion_set(all_asteroids_active.list[i].obj_centre);
							}
						}
					}
					// check whether the current asteroid under examination is close to screen centre, set up check to make sure new ship dosnt appear in asteroid
					if (all_asteroids_active.list[i].proxmity_to_centre_of_screen()) game.asteroid_too_close_to_reset_position = true;

					// has an asteroid hit the player ship?
					for (int j = 0; j < player.ship.num_pts - 3; ++j) { // check for ship and not rear jet triangle
						if (all_asteroids_active.list[i].collider({ player.ship.vertices[j].x, player.ship.vertices[j].y }) && player.ship.on_off) {
							player.ship.got_hit();
							Mix_PlayChannel(-1, sounds.ship_explode, 0);
							player_bullets.all_bullets_off();
						}
					}
				}
				// if the asteroid has been hit then keep explosion going until finished
				all_asteroids_active.list[i].obj_explosion();
			}

			// if the ship has been destroyed, the ships explosion has finished and there's no asteroid really close to the centre of the screen then the player ship can be reset
			if (!player.ship.on_off && !game.asteroid_too_close_to_reset_position && !player.ship.explode) { player.ship.reset_pos(); }

			// check whether the big saucer has hit the player
			for (int j = 0; j < player.ship.num_pts - 3; ++j) {
				if (big_enemy.ship.collider({ player.ship.vertices[j].x, player.ship.vertices[j].y }) && big_enemy.ship.on_off && player.ship.on_off) {
					//	std::cout <<"big saucer hit player ship\n";
					big_enemy.ship.destroy_enemy_ship(game.start_time);
					player.ship.got_hit();
					Mix_PlayChannel(-1, sounds.ship_explode, 0);
					player_bullets.all_bullets_off();
				}
			}

			// check whether the small saucer has hit the player
			for (int j = 0; j < player.ship.num_pts - 3; ++j) {
				if (small_enemy.ship.collider({ player.ship.vertices[j].x, player.ship.vertices[j].y }) && small_enemy.ship.on_off  && player.ship.on_off) {
					//	std::cout << "small saucer hit player ship\n";
					--player.ship.lives;
					small_enemy.ship.destroy_enemy_ship(game.start_time);
					player.ship.got_hit();
					Mix_PlayChannel(-1, sounds.ship_explode, 0);
					player_bullets.all_bullets_off();
				}
			}

			// check whether the small saucer has shot the player
			for (int i = 0; i < enemy_bullets.list.size(); ++i) {
				if (enemy_bullets.list[i].on_off) {
					if (player.ship.collider({ static_cast <int>(enemy_bullets.list[i].position.x), static_cast <int>(enemy_bullets.list[i].position.y) }) && player.ship.on_off) {
						//	std::cout << "small saucer shot player ship\n";
						player.ship.got_hit();
						Mix_PlayChannel(-1, sounds.ship_explode, 0);
						player_bullets.all_bullets_off();
					}
				}
			}

			// if the player has been hit then keep explosion going until finished 
			if (player.ship.explode) player.ship.split_apart();

			if (player.ship.on_off) {
				player.ship.move();
				player.ship.draw();

			// move player bullets if fired
				std::for_each(player_bullets.list.begin(), player_bullets.list.end(), [](bullet &bullet) {
					if (bullet.on_off) {
						bullet.move();
						bullet.draw();
					}
				});
			}

			// check timing interval and launch big saucer when required and then check for player bullet impacts as it flys around screen
			if (game.start_time > big_enemy.ship.start_time + big_enemy.ship.visit_interval) {
				big_enemy.ship.check_launch_enemy_ship();
			}
			if (big_enemy.ship.on_off) {
				if (big_enemy.ship.check_enemy_ship_bullet_hit(player_bullets, game.start_time)) {
					//	std::cout << "big saucer hit!\n";
					Mix_PlayChannel(-1, sounds.explode_big_asteroid, 0);
					player.ship.score += big_enemy.ship.score;
					big_enemy.ship.start_time = game.start_time;
				};
				sounds.big_saucer_count > 7 ? Mix_PlayChannel(-1, sounds.saucer_big, 0), sounds.big_saucer_count = 0 : ++sounds.big_saucer_count;
				big_enemy.ship.move();
				big_enemy.ship.draw();
			}
			// if the big saucer has been hit then keep explosion going until finished 
			big_enemy.ship.obj_explosion();

			// check timing interval and launch small saucer when required and then check for player bullet impacts as it flys around screen
			if (game.start_time > small_enemy.ship.start_time + small_enemy.ship.visit_interval) {
				small_enemy.ship.check_launch_enemy_ship();
			}
			if (small_enemy.ship.on_off) {
				if (small_enemy.ship.check_enemy_ship_bullet_hit(player_bullets, game.start_time)) {
					//	std::cout << "small saucer hit!\n";
					Mix_PlayChannel(-1, sounds.explode_medium_asteroid, 0);
					player.ship.score += small_enemy.ship.score;
					std::for_each(enemy_bullets.list.begin(), enemy_bullets.list.end(), [](bullet &bullet) {
						bullet.on_off = false;
					});
				};
				sounds.small_saucer_count > 5 ? Mix_PlayChannel(-1, sounds.saucer_small, 0), sounds.small_saucer_count = 0 : ++sounds.small_saucer_count;
				small_enemy.ship.move();
				small_enemy.ship.draw();
				// move small saucer bullets 
				std::for_each(enemy_bullets.list.begin(), enemy_bullets.list.end(), [](bullet &bullet) {
					++bullet.delay;
					if (bullet.on_off) {
						bullet.move();
						bullet.draw();
					}
				});
			}
			// keep small saucer explosion going as required
			small_enemy.ship.obj_explosion();

			// don't fire any small saucer bullets until well inside screen border. Distrbute bullets in a random polar coordinate pattern. fire from small ship vertex 0 arbitary
			if (small_enemy.ship.obj_centre.x > small_enemy.ship.fire_border && small_enemy.ship.obj_centre.x < window_X - small_enemy.ship.fire_border) {
				std::for_each(enemy_bullets.list.begin(), enemy_bullets.list.end(), [&](bullet &bullet) {
					if (!bullet.on_off && bullet.delay > small_enemy.ship.delay) {
						bullet.fire(small_enemy.ship.vertices[0], small_enemy.ship.rand_angle());
					}
				});
			}

			// show remaining lives as triangles under score. reset remaining lives list to match number of lives of player ship and then draw each one
			for (int i = 0; i < 10; ++i) {
				remaining_lives.list[i].on_off = false;
				if (i < player.ship.lives) { remaining_lives.list[i].on_off = true; }
			}

			std::for_each(remaining_lives.list.begin(), remaining_lives.list.end(), [](show_remain_lives &life) {
				if (life.on_off) {
					life.draw();
				}
			});

			// Has the player lost his last life?
			if (player.ship.lives < 1) {
				game_over.display(window_X / 3, 2 * window_Y / 5, window::renderer);
				restart.display(window_X / 4, 3 * window_Y / 5, window::renderer);
				player.ship.on_off = false;
				game.game_over = true;
				sounds.beat_count = 0;
				sounds.big_saucer_count = 0;
				sounds.small_saucer_count = 0;
			}

			// game over and restart the game if r is pressed 
			if (game.game_over && game.keystate[SDL_SCANCODE_R]) {
				small_enemy.ship.destroy_enemy_ship(game.start_time);
				big_enemy.ship.destroy_enemy_ship(game.start_time);
				player.ship.new_game();
				game.game_reset();
				all_asteroids_active.reset(original);
				for (int i = 0; i < 84; ++i) all_asteroids_active.list[i].on_off = false;
				for(int i=0; i < all_asteroids_active.list[0].start_count; ++i) all_asteroids_active.list[i].on_off = true;
				player.ship.reset_pos();
			}
			// if we're playing the game then sample ship controls and respond accordingly
			if (player.ship.on_off) {
				if (game.keystate[SDL_SCANCODE_LEFT]) { player.ship.rotate_left(); }
				if (game.keystate[SDL_SCANCODE_RIGHT]) { player.ship.rotate_right(); }
				if (game.keystate[SDL_SCANCODE_UP]) { 
					player.ship.thrust(); 
					player.ship.show_thrust = true;
					Mix_PlayChannel(-1, sounds.ship_thrust, 0);
				}
				if (!game.keystate[SDL_SCANCODE_UP]) { player.ship.show_thrust = false; }


				if (game.keystate[SDL_SCANCODE_Z]) { player.ship.hyperspace(); }

				if (game.keystate[SDL_SCANCODE_SPACE] && asteroid_window.space_key_release) {
					asteroid_window.space_key_release = false;
					for (auto i = 0; i < player_bullets.list.size(); ++i) {
						if (!player_bullets.list[i].on_off) {
							Mix_PlayChannel(-1, sounds.ship_shoot, 0);
							player_bullets.list[i].fire(player.ship.vertices[0], player.ship.ship_orientation);
							break;
						}
					}
				}
			}
			// make sure player has to press space everytime they want to fire a bullet, no automatic firing
			if (!game.keystate[SDL_SCANCODE_SPACE]) asteroid_window.space_key_release = true;

			// shot all the rocks, go up a level, increase the number of initial big asteroids and start again
			if (!game.one_left) {
				if (game.new_level_chk){ game.level_start_time = SDL_GetTicks(); game.new_level_chk = false; }
				if (game.level_new_time < game.level_start_time + game.new_level_delay) {
					game.level_new_time = SDL_GetTicks();
					level_num.display(window_X / 2, window_Y / 2, window::renderer);
				}
				else {
					++game.level;
					game.new_level_chk = true;
					game.level = std::min(all_asteroids_active.list[0].num_of_big_rock, game.level);
					all_asteroids_active.reset(original);
					for (int i = 0; i < game.level + all_asteroids_active.list[0].start_count; ++i) {
						all_asteroids_active.list[i].on_off = true;
					}
					player.ship.reset_pos(); //if we reset all rocks to their initial pre-determined positions and player to middle of screen then dont need to check for accidental collisions
				}
			}
			else { game.one_left = false; }
			asteroid_window.clear();
		}
	}

	return 0;
}


