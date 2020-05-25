#include "engine.h"

#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <algorithm>

#include<vector>

#include "animated_texture.h"
#include "Texture.h"
#include "game_object.h"


Engine::Engine(std::string window_name, Configuration* config) {
	const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
	const int init_result_success = 0;
	if (init_result != init_result_success)
					{
		std::cout << "Failed to initialize SDL" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const char* game_title = window_name.c_str();
	const int x = 100;
	const int y = 100;
	const int w = 600;
	const int h = 600;

	_window = SDL_CreateWindow(game_title, x, y, config->window_width, config->window_height, SDL_WINDOW_RESIZABLE);
	if (_window == nullptr)
	{
		std::cout << "Failed to create SDL window" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	const int first_renderer = -1;
	_renderer = SDL_CreateRenderer(_window, first_renderer, 0);
	if (_renderer == nullptr)
	{
		std::cout << "Failed to create Renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int image_init_result = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	const int image_init_success = IMG_INIT_JPG | IMG_INIT_PNG;
	if (image_init_result != image_init_success)
	{
		std::cout << "Failed to initialize SDL Image" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
		
	const int ttf_init_result = TTF_Init();
	const int ttf_init_success = 0;
	if (ttf_init_result != ttf_init_success)
	{
		std::cout << "Failed to initialize SDL TTF" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}


	const int mixer_init_result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	const int mixer_init_success = 0;
	if (mixer_init_result != mixer_init_success)
	{
		std::cout << "Failed to initialize SDL Mixer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		std::cout << "Mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}
	Mix_AllocateChannels(3);


}
Engine::~Engine() {}
void Engine::simulate(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Configuration* config) {
	simulate_AI(milliseconds_to_simulate, assets, scene, input);
	simulate_physics(milliseconds_to_simulate, assets, scene);
	render(milliseconds_to_simulate, assets, scene, config);

}
void Engine::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input) {

	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	for (Game_Object* game_object: game_objects)
	{
		game_object->simulate_AI(milliseconds_to_simulate,assets,input,scene);
	}
}
void Engine::simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene) {

	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	for (Game_Object* game_object : game_objects)
	{
		game_object->simulate_physics(milliseconds_to_simulate, assets, scene);
	}
}
void Engine::render(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Configuration* config) {
	const int render_clear_success = 0;
	const int render_clear_result = SDL_RenderClear(_renderer);
	if (render_clear_result != render_clear_success)
	{
		std::cout << "Failed to clear renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const SDL_Color background = scene->background_color();
	const int render_color_success = 0;
	const int render_color_result = SDL_SetRenderDrawColor(_renderer, background.r, background.g, background.b, 255);
	if (render_color_result != render_color_success)
	{
		{
			std::cout << "Failed to set render color" << std::endl;
			std::cout << "SDL Error: " << SDL_GetError() << std::endl;
			exit(1);
		}
	}


	/*Texture dino = Texture("Assets/dino.bmp", _renderer);
	SDL_Rect destination;
	destination.x = 220;
	destination.y = 220;
	destination.w = 200;

	destination.h = 200;
	dino.render(_renderer,nullptr,&destination,SDL_FLIP_NONE );*/
	{/*Texture* dino = (Texture*)assets->get_asset("Texture.Dino");
	SDL_Rect destination;
	destination.x = 50;
	destination.y = 50;
	destination.w = 100;
	destination.h = 100;*/
	

	}
	
		/*std::vector<Game_Object*> game_objects = scene->get_game_objects();
		for (Game_Object* game_object : game_objects)
		{
			game_object->render(milliseconds_to_simulate, assets, _renderer);
		}*/
		std::vector<Game_Object*> sorted_game_objects = scene->get_game_objects();
		const struct
		{
			bool operator()(Game_Object* a, Game_Object* b)
			{
				return a->translation().y() < b->translation().y();
			}
		} sort_by_y_order;
		std::sort(sorted_game_objects.begin(), sorted_game_objects.end(), sort_by_y_order);

		for (Game_Object* game_object : sorted_game_objects)
		{
			game_object->render(milliseconds_to_simulate, assets, _renderer, config,scene);
		}

		SDL_RenderPresent(_renderer);
	
	/*{
		const int frame_count = 10;
		const Uint32 frame_duration_milliseconds = 200;

		Animated_Texture* walking_dino = (Animated_Texture*)assets->get_asset("Texture.Dino.Walking");

		walking_dino->update_frame(milliseconds_to_simulate);

		SDL_Rect destination;
		destination.x = 250;
		destination.y = 50;
		destination.w = 100;
		destination.h = 100;
		walking_dino->render(_renderer, nullptr, &destination, SDL_FLIP_NONE);

	}

	{
		Animated_Texture* man = (Animated_Texture*)assets->get_asset("man");

		man->update_frame(milliseconds_to_simulate);

		SDL_Rect destination;
		destination.x = 350;
		destination.y = 200;
		destination.w = 100;
		destination.h = 100;
		man->render(_renderer, nullptr, &destination, SDL_FLIP_VERTICAL);
	}
	{
		Animated_Texture* zombie = (Animated_Texture*)assets->get_asset("zombie");

		zombie->update_frame(milliseconds_to_simulate);

		SDL_Rect destination;
		destination.x = 250;
		destination.y = 400;
		destination.w = 100;
		destination.h = 100;
		zombie->render(_renderer, nullptr, &destination, SDL_FLIP_VERTICAL);
	}
	{
		Animated_Texture* coin = (Animated_Texture*)assets->get_asset("coin");

		coin->update_frame(milliseconds_to_simulate);

		SDL_Rect destination;
		destination.x = 450;
		destination.y = 400;
		destination.w = 150;
		destination.h = 150;
		coin->render(_renderer, nullptr, &destination, SDL_FLIP_HORIZONTAL);
	}
	{
		Animated_Texture* girl = (Animated_Texture*)assets->get_asset("girl");

		girl->update_frame(milliseconds_to_simulate);

		SDL_Rect destination;
		destination.x = 50;
		destination.y = 400;
		destination.w = 150;
		destination.h = 150;
		girl->render(_renderer, nullptr, &destination, SDL_FLIP_HORIZONTAL);
	}
	{
		Animated_Texture* run = (Animated_Texture*)assets->get_asset("run");

		run->update_frame(milliseconds_to_simulate);

		SDL_Rect destination;
		destination.x = 50;
		destination.y = 200;
		destination.w = 150;
		destination.h = 150;
		run->render(_renderer, nullptr, &destination, SDL_FLIP_NONE);
	}

	*/


	SDL_RenderPresent(_renderer);
}



SDL_Renderer* Engine::renderer()
{
	return _renderer;
}

SDL_Window* Engine::window()
{
	return _window;
}