#pragma once

#include "portal_purple.h"
#include "enemy.h"
#include <ctime>


Portal_Exit::Portal_Exit(std::string id)
	: Game_Object(id, "Texture.portal.purple")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(100, -200);
	_time_until_spawn_enemy = 2000;	
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

void Portal_Exit::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* scene)
{
	_time_until_spawn_enemy -= milliseconds_to_simulate;

	if (_time_until_spawn_enemy <= 0)
	{
		Enemy* enemy = new Enemy("enemy" + std::to_string(time(0)));
		Game_Object* player = scene->get_game_object("player");

		Vector_2D this_to_player = player->translation() - _translation;
		this_to_player.normalize();
		this_to_player.scale(0.25);

		enemy->set_translation(_translation);
     	enemy->set_velocity(this_to_player);
		

		scene->add_game_object(enemy);

		_time_until_spawn_enemy = 2000;
	}
}