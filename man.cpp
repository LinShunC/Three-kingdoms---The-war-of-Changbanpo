#pragma once

#include "man.h"

Man::Man(std::string id)
	: Game_Object(id, "man")
{
	_translation = Vector_2D(450, 350);
}
Man::~Man()
{
}

void Man::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer,config, scene);
}

void Man::simulate_AI(Uint32, Assets*, Input*, Scene* )
{
}