#include <algorithm>    // std::min_element, std::max_element

#include "color_obj.hpp"
#include "bullet.hpp"

#include "bullet_data.hpp"

int const bullet::max_range = BULLET_RANGE;
int bullet::delay = ENEMY_FIRE_DELAY;
pointd bullet::off_position = BULLET_OFF_POSITION;
int const bullet::w = BULLET_HEIGHT;
int const bullet::h = BULLET_WIDTH;

bullet::bullet(const double &_speed) :
	position{ off_position },
	on_off{ false },
	speed{ _speed },
	range{0},
	bullet_angle{0}
{}

void bullet::draw() const {
	SDL_Rect rect = { position.x, position.y, w, h };
	SDL_SetRenderDrawColor(window::renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(window::renderer, &rect);
}

void bullet::fire(const SDL_Point &_bullet_origin, const double &_ship_orientation) {
	position.x = _bullet_origin.x;
	position.y = _bullet_origin.y;
	bullet_angle = _ship_orientation;
	range = 0;
	on_off = true;
};

void bullet::move() {
	position.x += speed * cos(bullet_angle);
	position.y += speed * sin(bullet_angle);
	range += speed;
	if (range > max_range) { position = off_position; on_off = false; }
};

player_bullet_list::player_bullet_list()
 {
	for (int i = 0; i < NUM_BULLETS; ++i) {
		bullet bullet(PLAYER_BULLET_SPEED);
		list.push_back(bullet);
	}
};

enemy_bullet_list::enemy_bullet_list()
{
	for (int i = 0; i < NUM_ENEMY_BULLETS_SMALL_SHIP; ++i) {
		bullet bullet(ENEMY_BULLET_SPEED);
		list.push_back(bullet);
	}
};

void player_bullet_list::all_bullets_off() {
	for (int i = 0; i < list.size(); ++i) {
		list[i].position = BULLET_OFF_POSITION;
		list[i].on_off = false;
	}
}