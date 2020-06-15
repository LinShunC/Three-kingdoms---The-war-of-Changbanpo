#pragma once

#include "Knight.h"
#include "player.h"
#include "sword.h"
#include <iostream>


Knight::Knight(std::string id)
	: Game_Object(id, "knight.run"), _generator(1337)
{
	int y = rand() % 100 +500;
	_translation = Vector_2D(650, (float)y);
	_velocity = Vector_2D(-0.1f, 0);

	time_when_dead = 890;
	_change_direction_timer = 0;


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

void Knight::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* scene )
{
	_change_direction_timer -= milliseconds_to_simulate;


	Player* player = (Player*)scene->get_game_object("player");
	player->getState();

	Vector_2D portal_center = _translation
		+ Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation()
		+ Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_center - player_center).magnitude();

	if (player->getState() == "attack" && distance_to_player <= 60.f)
	{
		Knight* knight = (Knight*)scene->get_game_object(id());
		knight->setID("knight.dead");

	}
	else  if (_texture_id != "knight.dead")
	{
		player->DistanceToEnemy(distance_to_player);
	}
	if (_texture_id == "knight.dead")
	{
		set_velocity(Vector_2D(0, 0));
		time_when_dead -= milliseconds_to_simulate;
		if (time_when_dead <= 0)
		{
			_boss_message = false;
			_to_be_destroyed = true;

			scene->add_game_object(new Sword("sword"));
			Sword* sword = (Sword*)scene->get_game_object("sword");
			sword->set_translation(_translation);
			sword->setOriginalTranslation(_translation);
		

		}

	}


	if (distance_to_player < 100.0f && player->getState() != "Dieing")
	{

		Vector_2D this_to_player = player->translation() - _translation;
		this_to_player.normalize();
		this_to_player.scale(0.1f);
		set_translation(_translation);
		set_velocity(this_to_player);

		_boss_message = true;

	}
	else 
	{
		_boss_message = false;
	}
	if (_change_direction_timer <= 0)
	{
		float random_x = ((float)_generator() / _generator.max()) * 2 - 1;
		float random_y = ((float)_generator() / _generator.max()) * 2 - 1;

		Vector_2D random_vector = Vector_2D(random_x, random_y);
		random_vector.normalize();
		random_vector.scale(0.02f);

		_velocity += random_vector;
		_velocity.normalize();
		_velocity.scale(0.2f);

		_change_direction_timer = 1000;
	}

}

void Knight::setID(string id)
{
	_texture_id = id;
}



