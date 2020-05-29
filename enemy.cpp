#pragma once

#include "enemy.h"
#include "player.h"

int time_when_dead = 890;

Enemy::Enemy(std::string id)
	: Game_Object(id, "enemy.run")
{
	int y  = rand() % 200;
	_translation = Vector_2D(350, (float) -y);
	_velocity = Vector_2D(-0.1f, 0);
	dead_time = 0;
}
Enemy::~Enemy()
{
}

void Enemy::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Enemy::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* scene)
{


	Player* player = (Player*)scene->get_game_object("player");
	player->getState();
     
	Vector_2D portal_center = _translation
		+ Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation()
		+ Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_center - player_center).magnitude();

	if (player->getState() == "attack" && distance_to_player <= 60.f) 
	{
		Enemy* enemy = (Enemy*)scene->get_game_object(id());
		enemy->setID("enemy.dieing");
		player->DistanceToEnemy(distance_to_player);

	}
	else  if (_texture_id != "enemy.dieing")
	{
		player->DistanceToEnemy(distance_to_player);
	}
	
	if (_texture_id == "enemy.run" && time_when_dead <= 0)
	{
		time_when_dead = 890;
	}
	


	 if (_texture_id == "enemy.dieing")
	{
		
		time_when_dead -= milliseconds_to_simulate;
			if (time_when_dead <= 0)
			{
				scene->remove_game_object(id());
				
			}
		
	}

}

void Enemy::setID(string id)
{
	_texture_id = id;
}



