#pragma once

#include <iostream>
#include <algorithm>    // std::min_element, std::max_element

class bullet 
{
public:
	bullet(const double &_speed) :
		position{ off_position },
		on_off{ false },
		speed {_speed }		
	{}

	~bullet() = default;

	void draw() const {
		SDL_Rect rect = { position.x, position.y, w, h };
		SDL_SetRenderDrawColor(window::renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(window::renderer, &rect);
	}

	void fire(const SDL_Point &_bullet_origin, double _ship_orientation) {
		position.x = _bullet_origin.x;
		position.y = _bullet_origin.y;
		bullet_angle = _ship_orientation;
		range = 0;
		on_off = true;
	};

	void move() {
		position.x += speed * cos(bullet_angle);
		position.y += speed * sin(bullet_angle);
		range += speed;
		if (range > BULLET_RANGE) { position = off_position; on_off = false; }
	};

	
	bool on_off;
	pointd position; 
	double bullet_angle;
	int delay{ ENEMY_FIRE_DELAY };
	double speed{};

private:
	pointd off_position{ BULLET_OFF_POSITION };
	double range;
	int w{ BULLET_HEIGHT };
	int h{ BULLET_WIDTH };
};