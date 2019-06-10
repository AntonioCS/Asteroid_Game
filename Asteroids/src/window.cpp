#include<iostream>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "window.hpp"

SDL_Renderer *window::renderer = nullptr;

window::window(const std::string &_title, int _width, int _height) :
	title{ _title },
	width{ _width },
	height{ _height }
{
	closed = !init();
}

window::~window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(asteroid_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialise SDL.\n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "Failed to intialise SDL_image.\n";
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "Failed to intialise SDL_ttf.\n";
		return false;
	}
	asteroid_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height, 0
	);

	if (asteroid_window == nullptr) {
		std::cerr << "Failed to create window.\n";
		return false;
	}

	window::renderer = SDL_CreateRenderer(asteroid_window, -1, SDL_RENDERER_ACCELERATED);

	if (window::renderer == nullptr) {
		std::cerr << "Failed to create renderer.\n";
		return false;
	}

	return true;
};

void window::poll_all_events(const Uint8 *keystate) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		x_close_chk(event);
	}
	if (keystate[SDL_SCANCODE_ESCAPE]) {
		closed = true;
	}
}

void window::x_close_chk(SDL_Event &event) {
	if (event.type == SDL_QUIT) {
		closed = true;
	}
}

void window::clear() const {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // sets background color for renderer
	SDL_RenderClear(renderer); // gets color onto renderer
}

int window::get_refresh_rate() {
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	int refresh_rate = mode.refresh_rate;
	std::cout << "Display Mode Refresh Rate = " << refresh_rate << " and Screen Refresh Rate = " << 1000 / refresh_rate  << "\n";
	return 1000/refresh_rate;
}


