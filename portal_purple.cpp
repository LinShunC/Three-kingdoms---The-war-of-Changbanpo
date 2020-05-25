#pragma once

#include "portal_purple.h"

Portal_Exit::Portal_Exit(std::string id)
	: Game_Object(id, "Texture.portal.purple")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(550, 300);
}
Portal_Exit::~Portal_Exit()
{
}

void Portal_Exit::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Portal_Exit::simulate_AI(Uint32, Assets*, Input*, Scene* )
{
}