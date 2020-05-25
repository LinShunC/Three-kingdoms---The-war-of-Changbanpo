#pragma once

#include "walking_dino.h"

Walking_Dino::Walking_Dino(std::string id)
	: Game_Object(id, "Texture.Dino.Walking")
{
	_translation = Vector_2D(150, 50);
	_velocity = Vector_2D(0.01f, 0);
	
}
Walking_Dino::~Walking_Dino()
{
}

void Walking_Dino::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer,config,scene);
}

void Walking_Dino::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	if (_translation.x() > 200.f && !_has_spawned_another) 
	{
		scene->add_game_object(new Walking_Dino(id() + ".Next"));
		_has_spawned_another = true;
	}
	else if(_translation.x()>400.f)
	{
		scene->remove_game_object(id());
	}
}