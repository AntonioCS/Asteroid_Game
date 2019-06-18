#pragma once

#include <iostream>
#include <vector>

#include "pointd.hpp"
#include <SDL_image.h>

#include "window.hpp"

class bullet 
{
public:
	explicit bullet(const double &_speed);

	~bullet() = default;

	void draw() const;
	void fire(const SDL_Point &_bullet_origin, const double &_ship_orientation);
	void move();

	bool on_off;
	pointd position; 
	double bullet_angle;
	static int delay; // enemy fire delay between bullets
	double speed;
	static pointd off_position;

private:
	double range{ 0 };
	static const int w;
	static const int h;
	static const int max_range;
};

class player_bullet_list {
public:
	player_bullet_list();
	~player_bullet_list() = default;
	void all_bullets_off();
	std::vector<bullet> list;
};

class enemy_bullet_list {
public:
	enemy_bullet_list();
	~enemy_bullet_list() = default;
	std::vector<bullet> list;
};

