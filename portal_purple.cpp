#pragma once

#include "portal_purple.h"
#include "enemy.h"
#include "player.h"
#include "Knight.h"
#include <ctime>
#include <iostream>


Portal_Exit::Portal_Exit(std::string id)
	: Game_Object(id, "Texture.portal.purple")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(1100, -1200);
	_time_until_spawn_enemy = 3000;	
	should_spawn_boss = true;
	should_spawn_equipment = false;

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
	Player* player = (Player*) scene->get_game_object("player");
	std::vector<Game_Object*> game_objects = scene->get_game_objects();
	should_spawn = true;
	for (Game_Object* game_object : game_objects)
	{
		if (game_object->id().find("enemy") != string::npos)
		{
			should_spawn = false;
		}
	
	//	cout << game_object->id().find("enemy") << endl;
		
	}
	if (player->getDeadTimes() < 3) {
		if (_time_until_spawn_enemy <= 0 && should_spawn)
		{
			Enemy* enemy = new Enemy("enemy" + std::to_string(time(0)));

		
			scene->add_game_object(enemy);
			should_spawn = false;
			_time_until_spawn_enemy = 2000;
		}
	}
	else if (player->getDeadTimes() >= 3 && should_spawn_boss)
	{
		scene->add_game_object(new Knight("Knight"));
		should_spawn_boss = false;
	}
	
}