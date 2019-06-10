#pragma once

struct msg {
	int score_font_size{ 20 };
	int game_message_font_size{ 12 };
	std::string font{ "D:/CPP_Games/Asteroids/Asteroids/data/Vector_Battle.ttf" };
};

msg msg{};

// adjust size of all the main game elments to make realstic looking game
// use of template allows for object and scale to be used together, othwise get type incompatible error
template<typename T, std::size_t type_num, std::size_t vertex_num>
void scale_game_object_data(T(&object_ref_data)[type_num][vertex_num], const double scale) {
	for (int i = 0; i < type_num; ++i) {
		for (int j = 0; j < vertex_num; ++j) {
			object_ref_data[i][j].x *= scale;
			object_ref_data[i][j].y *= scale;
		}
	}
}

template<typename T, std::size_t vertex_num>
void scale_game_object_data(T(&object_ref_data)[vertex_num], const double scale) {
	for (int j = 0; j < vertex_num; ++j) {
		object_ref_data[j].x *= scale;
		object_ref_data[j].y *= scale;
	}
}

// adjust size of all the main game elments to make realstic looking game
void scale_all_game_objects() {
	scale_game_object_data(big_rocks_ref, SCALE_BIG_ROCK);
	scale_game_object_data(medium_rocks_ref, SCALE_MEDIUM_ROCK);
	scale_game_object_data(small_rocks_ref, SCALE_SMALL_ROCK);
	scale_game_object_data(player_space_ship_ref, SCALE_PLAYER_SHIP);
	scale_game_object_data(player_space_ship, SCALE_PLAYER_SHIP);
	scale_game_object_data(big_enemy_ship_ref, SCALE_BIG_ENEMY_SHIP);
	scale_game_object_data(small_enemy_ship_ref, SCALE_SMALL_ENEMY_SHIP);
}

std::vector<asteroid> initialise_rocks() {
	std::vector<asteroid> asteroid_list; 
	int index = 0;
	for (int i = 0; i < TOTAL_ROCKS; ++i) {
		for (int j = 0; j < ROCK_VERTEX_COUNT; ++j) {
			if (i < 12) { rocks[i][j] = big_rocks_ref[index][j]; }
			else if (i >= 12 && i < 36) { rocks[i][j] = medium_rocks_ref[index][j]; }
			else { rocks[i][j] = small_rocks_ref[index][j]; } 
		};
		index > (ROCK_TYPE_COUNT - 2) ? index = 0 : index++;
	}
	for (int i = 0; i < 12; ++i) {
			asteroid asteroid(rocks[i], BIG_ROCK_VERTEX_COUNT, intial_position_big_rocks[i], initial_velocity_big_rocks[i], show_big_rocks[i], BIG_ROCK, 20);
			asteroid_list.push_back(asteroid);
		}
	for (int i = 12; i < 36; ++i) {
			asteroid asteroid(rocks[i], MEDIUM_ROCK_VERTEX_COUNT, intial_position_medium_rocks[i-12], initial_velocity_medium_rocks[i-12], show_medium_rocks[i-12], MEDIUM_ROCK, 50);
			asteroid_list.push_back(asteroid);
		}
	for (int i = 36; i < 84; ++i) {
			asteroid asteroid(rocks[i], SMALL_ROCK_VERTEX_COUNT, intial_position_small_rocks[i-36], initial_velocity_small_rocks[i-36], show_small_rocks[i-36], SMALL_ROCK, 100);
			asteroid_list.push_back(asteroid);
		}
	int c = { 0 };
	for (auto i : asteroid_list) {
		c++;
	}
return asteroid_list;
}

std::vector<bullet> make_bullets(const int &n, const double &s) {
	std::vector<bullet> bullet_list;
	for (int i = 0; i < n; ++i) {
		bullet bullet(s);
		bullet_list.push_back(bullet);
	}
	return bullet_list;
}

std::vector<show_remain_lives> remaining_lives() {
	for (int i = 0; i < SHOW_LIVES_COUNT; ++i) {
		for (int j = 0; j < SHOW_LIVES_VERTEX_COUNT; ++j) {
			show_lives[i][j] = show_lives_ref[j];
		}
	}
	std::vector<show_remain_lives> show_remain_lives_list;
	for (int i = 0; i < SHOW_LIVES_COUNT; ++i) {
		show_remain_lives show_remain_lives(show_lives[i], intial_position_show_lives[i], show_show_lives[i]);
		show_remain_lives_list.push_back(show_remain_lives);
	}
	return show_remain_lives_list;
}
