#pragma once

#include "zombie.h"
#include "input.h"

Zombie::Zombie(std::string id)
	: Game_Object(id, "zombie")
{
	_translation = Vector_2D(350, 450);
	_velocity = Vector_2D(0.01f, 0);

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width/2.0f,(float)_height));

}
Zombie::~Zombie()
{
}

void Zombie::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Zombie::simulate_AI(Uint32 , Assets*, Input* , Scene* )
{
	

}
