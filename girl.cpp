#pragma once

#include "girl.h"

Girl::Girl(std::string id)
	: Game_Object(id, "girl")
{
	_translation = Vector_2D(350, 250);
}
Girl::~Girl()
{
}

void Girl::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer,config, scene);
}

void Girl::simulate_AI(Uint32, Assets*, Input* ,Scene* )
{
	
}