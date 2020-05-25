#pragma once

#include <map>
#include <string>
#include <vector>
#include "vector_2D.h"
#include <SDL.h>

class Game_Object;

class Scene
{
public:
	Scene(std::string id);
	~Scene();
	Vector_2D camera_translation();

	virtual void update(SDL_Window* window) = 0;

	Game_Object* get_game_object(std::string id);
	std::vector<Game_Object*> get_game_objects();

	std::string id();

	void add_game_object(Game_Object* game_object);
	void remove_game_object(std::string id);

	SDL_Color background_color();

protected:

	Vector_2D _camera_translation;
	std::map<std::string, Game_Object*> _game_objects;
	std::string                         _id;
	SDL_Color                           _background_color;
};