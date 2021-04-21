#pragma once

#include <SDL2/SDL_mixer.h>
#include "window.hpp"

class sounds {
public:
	sounds() {
		ship_shoot = Mix_LoadWAV("sounds/ship_shoot.wav");
		if (ship_shoot == nullptr) std::cout << "ship shoot failed to load\n";

		ship_explode = Mix_LoadWAV("sounds/ship_explode.wav");
		if (ship_explode == nullptr) std::cout << "ship explode failed to load\n";

		ship_thrust = Mix_LoadWAV("sounds/ship_thrust.wav");
		if (ship_thrust == nullptr) std::cout << "ship thrust failed to load\n";

		explode_big_asteroid = Mix_LoadWAV("sounds/explode_big_asteroid.wav");
		if (explode_big_asteroid == nullptr) std::cout << "explode big asteroid failed to load\n";

		explode_medium_asteroid = Mix_LoadWAV("sounds/explode_medium_asteroid.wav");
		if (explode_medium_asteroid == nullptr) std::cout << "explode medium asteroid failed to load\n";

		explode_small_asteroid = Mix_LoadWAV("sounds/explode_small_asteroid.wav");
		if (explode_small_asteroid == nullptr) std::cout << "explode small asteroid failed to load\n";

		extra_ship = Mix_LoadWAV("sounds/extra_ship.wav");
		if (extra_ship == nullptr) std::cout << "extra ship sound failed to load\n";

		game_heart_beat = Mix_LoadWAV("sounds/game_heart_beat.wav");
		if (game_heart_beat == nullptr) std::cout << "game_heart_beat sound failed to load\n";

		saucer_big = Mix_LoadWAV("sounds/saucer_big.wav");
		if (saucer_big == nullptr) std::cout << "saucer_big sound failed to load\n";

		saucer_small = Mix_LoadWAV("sounds/saucer_small.wav");
		if (saucer_small == nullptr) std::cout << "saucer_small sound failed to load\n";

		hyperspace = Mix_LoadWAV("sounds/hyperspace.wav");
		if (saucer_small == nullptr) std::cout << "hyerspace sound failed to load\n";

	}
	~sounds() {
		Mix_FreeChunk(ship_shoot);
		ship_shoot = nullptr;

		Mix_FreeChunk(ship_explode);
		ship_explode = nullptr;

		Mix_FreeChunk(ship_thrust);
		ship_thrust = nullptr;

		Mix_FreeChunk(explode_big_asteroid);
		explode_big_asteroid = nullptr;

		Mix_FreeChunk(explode_medium_asteroid);
		explode_medium_asteroid = nullptr;

		Mix_FreeChunk(explode_small_asteroid);
		explode_small_asteroid = nullptr;

		Mix_FreeChunk(extra_ship);
		extra_ship = nullptr;

		Mix_FreeChunk(game_heart_beat);
		game_heart_beat = nullptr;

		Mix_FreeChunk(saucer_big);
		saucer_big = nullptr;

		Mix_FreeChunk(saucer_small);
		saucer_small = nullptr;

		Mix_FreeChunk(hyperspace);
		hyperspace = nullptr;
	};

	Mix_Chunk *ship_shoot = nullptr;
	Mix_Chunk *ship_explode = nullptr;
	Mix_Chunk *ship_thrust = nullptr;
	Mix_Chunk *explode_big_asteroid = nullptr;
	Mix_Chunk *explode_medium_asteroid = nullptr;
	Mix_Chunk *explode_small_asteroid = nullptr;
	Mix_Chunk *extra_ship = nullptr;
	Mix_Chunk *game_heart_beat = nullptr;
	Mix_Chunk *saucer_big = nullptr;
	Mix_Chunk *saucer_small = nullptr;
	Mix_Chunk *hyperspace = nullptr;

	int beat_count{ 0 };
	int big_saucer_count{ 0 };
	int small_saucer_count{ 0 };

}; 


