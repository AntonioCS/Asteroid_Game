#pragma once

#include <iostream>
#include <algorithm>

//constexpr auto PI_DEG = 180 / PI;  // for debug

struct ship_specification {
	double thrust{ 0.05 };
	double velocity_limit{ 4.0 };
	double ship_rotate_speed{ 0.04 };
	double mass{ 10.0 };
	double acceleration{ thrust / mass };
};

struct explode_shape {
	double line_length{};
	pointd line_centre{};
	double angle{};
};

class player_ship : public game_obj
{
public:
	player_ship(SDL_Point *_vertices, const int &_num_pts, SDL_Point _position, game_obj_velocity _av) :
		game_obj(_vertices, _num_pts, _position, _av, true)
	{}
	~player_ship() = default;

	void get_centre_rotation() {
		sc.x = (vertices[0].x + vertices[1].x + vertices[3].x) / 3.0;
		sc.y = (vertices[0].y + vertices[1].y + vertices[3].y) / 3.0;
	}

	void rotate_ship(const double &ship_orientation) {
		get_centre_rotation();
		// turn ship
		cos_a = cos(ship_orientation);
		sin_a = sin(ship_orientation);
		for (int i = 0; i < num_pts; ++i) {

			rotated_space_ship_X[i] = player_space_ship[i].x * cos_a - player_space_ship[i].y * sin_a;
			rotated_space_ship_Y[i] = player_space_ship[i].x * sin_a + player_space_ship[i].y * cos_a;

			vertices[i].x = sc.x + ceil(rotated_space_ship_X[i]);
			vertices[i].y = sc.y + ceil(rotated_space_ship_Y[i]);
		}
	}

	void check_rotational_limits(double &ship_orientation) {
		if (ship_orientation > 2 * PI) ship_orientation -= 2 * PI;
		if (ship_orientation < 0) ship_orientation += 2 * PI;
	}

	void rotate_left() {
		ship_orientation -= ship_specification.ship_rotate_speed;
		check_rotational_limits(ship_orientation);
		rotate_ship(ship_orientation);
	}

	void rotate_right() {
		ship_orientation += ship_specification.ship_rotate_speed;
		check_rotational_limits(ship_orientation);
		rotate_ship(ship_orientation);
	}

	void thrust() {
		av_vel_old = av.velocity;
		motion_orientation_delta_angle = ship_orientation - av.angle;
		cos_a = cos(motion_orientation_delta_angle);
		sin_a = sin(motion_orientation_delta_angle);
		// vector thrust and reorientate. review this and see if you can incorporate momentum etc..
		av.velocity += cos_a * ship_specification.thrust;
		sideways_velocity = sin_a * ship_specification.thrust;
		// limit maximum speed
		av.velocity = std::max(-ship_specification.velocity_limit, std::min(av.velocity, ship_specification.velocity_limit));
		if (av.velocity != av_vel_old) {
			av.angle += tan(sideways_velocity / av.velocity);
		}
	}


	void reset_pos() {
		for (auto i = 0; i < num_pts; ++i) {
			// centre back on screen
			vertices[i].x = window_X / 2.0 + player_space_ship[i].x;
			vertices[i].y = window_Y / 2.0 + player_space_ship[i].y;
		}
		av.angle = 0.0;
		av.velocity = 0;
		ship_orientation = 0.0;
		on_off = true;
		std::cout << "Reset Ship\n";
	}


	void hyperspace() {
		// to be done
	}

	void got_hit() {
		explode = true;
		on_off = false;
		--lives;
		get_centre_rotation();
		explode_centre = { sc.x, sc.y };
		explode_orientation = { ship_orientation };
		explode_count = 0;

		double tmp_line_length;
		pointd tmp_pos;
		double tmp_angle;
		explode_shape tmp_explode_line;
		explode_line_list.clear();

		for (int i = 0; i < num_pts - 3; ++i) {
			tmp_line_length = sqrt((vertices[i].x - vertices[i + 1].x)*(vertices[i].x - vertices[i + 1].x) + (vertices[i].y - vertices[i + 1].y)*(vertices[i].y - vertices[i + 1].y));
			tmp_pos = { (vertices[i].x + vertices[i + 1].x) / 2.0, (vertices[i].y + vertices[i + 1].y) / 2.0 };
			tmp_angle = atan2(vertices[i + 1].y - vertices[i].y, vertices[i + 1].x - vertices[i].x);
			tmp_explode_line = { tmp_line_length, tmp_pos, tmp_angle };
			explode_line_list.push_back(tmp_explode_line);

			if (tmp_pos.x > explode_centre.x) explode_step[i].x = +0.5;
			else explode_step[i].x = -1;

			if (tmp_pos.y > explode_centre.y) explode_step[i].y = +1;
			else explode_step[i].y = -1;
		}
	}

	void explode_player_ship() {
		SDL_SetRenderDrawColor(window::renderer, color.r, color.g, color.b, color.a);
		SDL_Point P1{ 0,0 };
		SDL_Point P2{ 0,0 };

		for (int i = 0; i < explode_line_list.size()-1; ++i) {

			explode_line_list[i].line_centre.x += explode_step[i].x;
			explode_line_list[i].line_centre.y += explode_step[i].y;
			explode_line_list[i].angle += explosion_part_rotation[i];

			P1.x = explode_line_list[i].line_centre.x + (0.5*explode_line_list[i].line_length)*cos(explode_line_list[i].angle);
			P1.y = explode_line_list[i].line_centre.y + (0.5*explode_line_list[i].line_length)*sin(explode_line_list[i].angle);
			P2.x = explode_line_list[i].line_centre.x - (0.5*explode_line_list[i].line_length)*cos(explode_line_list[i].angle);
			P2.y = explode_line_list[i].line_centre.y - (0.5*explode_line_list[i].line_length)*sin(explode_line_list[i].angle);
		
		SDL_RenderDrawLine(window::renderer, P1.x, P1.y, P2.x, P2.y);
		if (explode_count > expode_duration) { explode = false; 
		}
		++explode_count;
		}
	}

	virtual void draw() const override {
		SDL_SetRenderDrawColor(window::renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLines(window::renderer, vertices, num_pts - 3);
		if (show_thrust) SDL_RenderDrawLines(window::renderer, vertices + 5, 3);
	}

	double drag{ 1.00 }; //1.005
	double ship_orientation{ initial_velocity_ship.angle };
	bool show_thrust{ false };
	int player_score{ 0 };
	int lives{ START_LIVES_NUM };
	bool reset{ false };
	int extra_ship{ 10000 };

private:
	double av_vel_old{ initial_velocity_ship.velocity };
	pointd ship_momentum{ 0.0,0.0 };
	pointd thrust_force{ 0.0,0.0 };
	double motion_orientation_delta_angle{ initial_velocity_ship.angle };
	double sideways_velocity{};
	const ship_specification ship_specification;
	double cos_a{};
	double sin_a{};
	std::vector<int> vert_index{ 0,1,1,2,2,3,3,0 };
	double explode_orientation{ 0.0 };
	std::vector<explode_shape> explode_line_list{};
	std::vector<pointd> explode_step{ {0,0},{0,0},{0,0},{0,0},{0,0} };
	double explosion_rotation_spd{ 0.05 };
	std::vector<double> explosion_part_rotation{ explosion_rotation_spd, explosion_rotation_spd, explosion_rotation_spd, explosion_rotation_spd };
	int explode_count{0};
	int expode_duration{200};
	pointd sc{};
	double rotated_space_ship_X[TOTAL_SHIP_VERTEX_COUNT];
	double rotated_space_ship_Y[TOTAL_SHIP_VERTEX_COUNT];
	SDL_Point explode_vertices[2 * PLAYER_SHIP_VERTEX_COUNT - 2];

};
