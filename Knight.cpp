#pragma once

#include "Knight.h"
#include "player.h"
#include <iostream>

//int time_when_dead = 890;

Knight::Knight(std::string id)
	: Game_Object(id, "knight.run"), _generator(1337)
{
	int y = rand() % 200;
	_translation = Vector_2D(350, (float)-y);
	_velocity = Vector_2D(-0.1f, 0);

	_collider.set_radius(_width / 10.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));
	_change_direction_timer = 0;

	//	_exit_time = 2500;
}
Knight::~Knight()
{
}

void Knight::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Knight::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* )
{
	_change_direction_timer -= milliseconds_to_simulate;

	if (_change_direction_timer <= 0)
	{
		float random_x = ((float)_generator() / _generator.max()) * 2 - 1;
		float random_y = ((float)_generator() / _generator.max()) * 2 - 1;

		Vector_2D random_vector = Vector_2D(random_x, random_y);
		random_vector.normalize();
		random_vector.scale(0.02f);

		_velocity += random_vector;
		_velocity.normalize();
		_velocity.scale(0.05f);

		_change_direction_timer = 1000;
	}

}

void Knight::setID(string id)
{
	_texture_id = id;
}



