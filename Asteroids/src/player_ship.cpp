#include <iostream>

#include "player_ship.hpp"
#include "player_ship_data.hpp" // player ship reference data

// ship specification
double const ship_specification::thrust{ 0.05 };
double const ship_specification::velocity_limit{ 4.0 };
double const ship_specification::ship_rotate_speed{ 0.04 };
double const ship_specification::mass{ 10.0 };

double player_ship::rotated_space_ship_X[TOTAL_SHIP_VERTEX_COUNT]; 
double player_ship::rotated_space_ship_Y[TOTAL_SHIP_VERTEX_COUNT]; 
SDL_Point player_ship::explode_vertices[2 * (PLAYER_SHIP_VERTEX_COUNT) - 2]; 
double player_ship::drag{ SHIP_DRAG }; //1.005
int player_ship::score{ 0 };
int player_ship::lives{ START_LIVES_NUM };
int const player_ship::max_lives{ MAX_LIVES_NUM };
bool player_ship::show_thrust{ false };
bool player_ship::reset{ false };
int player_ship::extra_ship{ SCORE_FOR_EXTRA_SHIP };
int player_ship::hyperspace_num{ NUM_HPERSPACE };


pointd player_ship::thrust_force{ 0.0,0.0 };
//explosion vertex list
std::vector<int> player_ship::vert_index{ EXPLOSION_DRAW_VERTICES_REF };
std::vector<pointd> player_ship::explode_step{ {0,0},{0,0},{0,0},{0,0},{0,0} };
double player_ship::explosion_rotation_spd{ EXPLOSION_PIECES_ROTATION_SPEED };
std::vector<double> player_ship::explosion_part_rotation{ explosion_rotation_spd, explosion_rotation_spd, explosion_rotation_spd, explosion_rotation_spd };
int player_ship::explode_count{ 0 };
int player_ship::expode_duration{ EXPLOSION_RADIUS_DURATION };

player_ship::player_ship(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, const double &_scale) :
	game_obj(_vertices, _num_pts, _position, _av, true),
	ship_orientation{ av.angle },
	av_vel_old{ av.velocity },
	motion_orientation_delta_angle{ av.angle },
	scale {_scale}
{
	scale_game_object_data(player_space_ship_ref, scale);
	scale_game_object_data(player_space_ship, scale);
}

void player_ship::get_centre_rotation() {
	sc.x = (vertices[0].x + vertices[1].x + vertices[3].x) / 3.0;
	sc.y = (vertices[0].y + vertices[1].y + vertices[3].y) / 3.0;
}

void player_ship::rotate_ship(const double &ship_orientation) {
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

void player_ship::check_rotational_limits(double &ship_orientation) {
	if (ship_orientation > 2 * PI) ship_orientation -= 2 * PI;
	if (ship_orientation < 0) ship_orientation += 2 * PI;
}

void player_ship::rotate_left() {
	ship_orientation -= ship_specification.ship_rotate_speed;
	check_rotational_limits(ship_orientation);
	rotate_ship(ship_orientation);
}

void player_ship::rotate_right() {
	ship_orientation += ship_specification.ship_rotate_speed;
	check_rotational_limits(ship_orientation);
	rotate_ship(ship_orientation);
}

void player_ship::thrust() {
	motion_orientation_delta_angle = ship_orientation - av.angle;
	cos_a = cos(motion_orientation_delta_angle);
	sin_a = sin(motion_orientation_delta_angle);
	av.velocity += cos_a * ship_specification.thrust;
	sideways_velocity = sin_a * ship_specification.thrust;
	av.velocity = std::max(-ship_specification.velocity_limit, std::min(av.velocity, ship_specification.velocity_limit));
	av.angle += tan(sideways_velocity / av.velocity);
}

void player_ship::reset_pos() {
	for (auto i = 0; i < num_pts; ++i) {
		// centre back on screen
		vertices[i].x = window_X / 2.0 + player_space_ship[i].x;
		vertices[i].y = window_Y / 2.0 + player_space_ship[i].y;
	}
	av.angle = 0.0;
	av.velocity = 0;
	ship_orientation = 0.0;
	on_off = true;
}


void player_ship::hyperspace() {
	int X = hyper_space_coords().x;
	int Y = hyper_space_coords().y;
	for (auto i = 0; i < num_pts; ++i) {
		// centre back on screen
		vertices[i].x = X + player_space_ship[i].x;
		vertices[i].y = Y + player_space_ship[i].y;
	}
}

void player_ship::got_hit() {
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

void player_ship::split_apart() {
	SDL_SetRenderDrawColor(window::renderer, 200, 200, 200, 255);
	SDL_Point P1{ 0,0 };
	SDL_Point P2{ 0,0 };

	for (int i = 0; i < explode_line_list.size() - 1; ++i) {

		explode_line_list[i].line_centre.x += explode_step[i].x;
		explode_line_list[i].line_centre.y += explode_step[i].y;
		explode_line_list[i].angle += explosion_part_rotation[i];

		P1.x = explode_line_list[i].line_centre.x + (0.5*explode_line_list[i].line_length)*cos(explode_line_list[i].angle);
		P1.y = explode_line_list[i].line_centre.y + (0.5*explode_line_list[i].line_length)*sin(explode_line_list[i].angle);
		P2.x = explode_line_list[i].line_centre.x - (0.5*explode_line_list[i].line_length)*cos(explode_line_list[i].angle);
		P2.y = explode_line_list[i].line_centre.y - (0.5*explode_line_list[i].line_length)*sin(explode_line_list[i].angle);

		SDL_RenderDrawLine(window::renderer, P1.x, P1.y, P2.x, P2.y);
		if (explode_count > expode_duration) {
			explode = false;
		}
		++explode_count;
	}
}

void player_ship::draw() const {
	SDL_SetRenderDrawColor(window::renderer, 200, 200, 200, 255);
	SDL_RenderDrawLines(window::renderer, vertices, num_pts - 3);
	if (show_thrust) SDL_RenderDrawLines(window::renderer, vertices + 5, 3); // jet thrust triangle
}

ship_construct::ship_construct() {};
player_ship ship_construct::ship(player_space_ship_ref, TOTAL_SHIP_VERTEX_COUNT, intial_position_ship, initial_velocity_ship, SCALE_PLAYER_SHIP);

// Does the player get another ship
bool player_ship::earn_life(){
	if (score > extra_ship) {
	++lives;
	extra_ship += 10000;
	lives = std::min(10, lives);
	return true;
	}
	else return false;
}

void player_ship::new_game() {
	score = 0;
	lives = START_LIVES_NUM;
}