#include "_game_obj.hpp"
#include <vector>

#include "random_num.hpp"

RGB color;

game_obj::game_obj(SDL_Point *_vertices, const int &_num_pts, const SDL_Point &_position, game_obj_velocity _av, bool _on_off) :
	vertices{ _vertices }, // actual local vertex coordinates defining sape of object
	num_pts{ _num_pts }, // number of vertices
	position{ _position }, // initial position
	av{ _av }, // velocity vector of object
	on_off{ _on_off } // can we see the object on the screen
{
	for (int i = 0; i < num_pts; ++i) { // set the game object vertices in the correct position
		vertices[i].x += position.x;
		vertices[i].y += position.y;
	}
}

void game_obj::draw() const {
	SDL_SetRenderDrawColor(window::renderer, color.r, color.b, color.g, color.a);
	SDL_RenderDrawLines(window::renderer, vertices, num_pts);
}

double game_obj::rand_angle() const {
	return PIx2_RAND(gen);
}

int game_obj::rand_saucer_start_y() const {
	return window_Y_RAND(gen);
}

double game_obj::rand_nudge_angle() const {
	return RAND_0_to_1(gen);
}

pointd game_obj::hyper_space_coords() const {
	return { hyper_space_X(gen), hyper_space_Y(gen) };
}

void game_obj::check_boundaries() const {

	if (game_obj_box.x_min >= window_X) {
		for (auto i = 0; i < num_pts; ++i) {
			vertices[i].x -= game_obj_box.x_max - 1.0;
		}
	}
	if (game_obj_box.y_min >= window_Y) {
		for (auto i = 0; i < num_pts; ++i) {
			vertices[i].y -= game_obj_box.y_max - 1.0;
		}
	}
	if (game_obj_box.x_max <= 0) {
		for (auto i = 0; i < num_pts; ++i) {
			vertices[i].x += (window_X - game_obj_box.x_min - 1.0);
		}
	}
	if (game_obj_box.y_max <= 0) {
		for (auto i = 0; i < num_pts; ++i) {
			vertices[i].y += (window_Y - game_obj_box.y_min - 1.0);
		}
	}
}

void game_obj::move() {

	// calculate how much to move in x y coordinates
	ship_inc_pos.x += av.velocity * cos(av.angle);
	ship_inc_pos.y += av.velocity * sin(av.angle);

	// get the max and min vertex coordinates, define the box that contains the object
	std::for_each(vertices, vertices + num_pts, [&](SDL_Point p) {
		p.x > game_obj_box.x_max ? game_obj_box.x_max = p.x : game_obj_box.x_max;
		p.x < game_obj_box.x_min ? game_obj_box.x_min = p.x : game_obj_box.x_min;
		p.y > game_obj_box.y_max ? game_obj_box.y_max = p.y : game_obj_box.y_max;
		p.y < game_obj_box.y_min ? game_obj_box.y_min = p.y : game_obj_box.y_min;
	}
	);

	// calculate  the objects centre
	obj_centre = { (game_obj_box.x_max + game_obj_box.x_min) / 2.0, (game_obj_box.y_max + game_obj_box.y_min) / 2.0 };

	game_obj::check_boundaries();

	fabs_x = fabs(ship_inc_pos.x);
	fabs_y = fabs(ship_inc_pos.y);
	xf = round(ship_inc_pos.x);
	yf = round(ship_inc_pos.y);

	// this is a tricky bit as SDL_points are in ints and so very small incremental movement doesn't necessarily show correctly. object movement is therefore tracked using floating point precision but then incremented by rounding the floating points when required.
	if (fabs_x >= 1.0) {

		(ship_inc_pos.x > 0) ? ship_inc_pos.x = std::max(1, static_cast<int>(xf)) : ship_inc_pos.x = std::min(-1, static_cast<int>(xf));

		for (int i = 0; i < num_pts; ++i) {
			vertices[i].x += ship_inc_pos.x;
		}
		ship_inc_pos.x = 0;

	}

	if (fabs_y >= 1.0) {
		(ship_inc_pos.y > 0) ? ship_inc_pos.y = std::max(1, static_cast<int>(yf)) : ship_inc_pos.y = std::min(-1, static_cast<int>(yf));
		for (int i = 0; i < num_pts; ++i) {
			vertices[i].y += ship_inc_pos.y;
		}
		ship_inc_pos.y = 0;
	}
	game_obj_box = { 0, 0, window_X, window_Y };
}

/* I admit, I always have to look this one up all the time see, https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html. thanks for the help
// Run a semi-infinite ray horizontally (increasing x, fixed y) out from the test point, and count how many edges it crosses. At each crossing, the ray switches between inside and outside. This is called the Jordan curve theorem. Very cool isn't it!*/
bool game_obj::collider(const SDL_Point &point) const {

	int i, j, c = 0;
	for (i = 0, j = num_pts - 1; i < num_pts; j = i++) {
		if (((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
			(point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
			c = !c;
	}
	return c;
}

void game_obj::obj_explosion_set(const pointd & original_obj_centre) {
	explode = true;
	explode_radius = 0;
	explode_centre = { original_obj_centre.x, original_obj_centre.y };

	for (int n = 0; n < num_shrapnel; ++n) {
		explosion_stars[n].x = original_obj_centre.x;
		explosion_stars[n].y = original_obj_centre.y;
	}
}

void game_obj::obj_explosion() {
	if (explode && explode_radius < explosion_size*av.velocity) {
		++explode_radius;
		for (int n = 0; n < num_shrapnel; ++n) {
			explosion_stars[n].x = explode_centre.x + explode_radius * cos(n*PI / (num_shrapnel / 2));
			explosion_stars[n].y = explode_centre.y + explode_radius * sin(n*PI / (num_shrapnel / 2));
		}
		SDL_SetRenderDrawColor(window::renderer, color.r, color.g, color.r, color.a);
		SDL_RenderDrawPoints(window::renderer, explosion_stars, num_shrapnel);
	}
	else {
		explode = false;
		explode_radius = 0;
	}
}

