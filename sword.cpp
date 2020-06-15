#pragma once

#include "sword.h"
#include "player.h"

Sword::Sword(std::string id)
	: Game_Object(id, "Sword") , _originalTranslation(0, 0)
{

	_height = 150;
	_width = 150;
	flip_direction = 0;
}

Sword::~Sword()
{
}
void Sword::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	Sword* sword = (Sword*)scene->get_game_object("sword");

	//sword->_flip = SDL_FLIP_VERTICAL;
	if (_translation.y() < _originalTranslation.y() - 100) 
	{
		_flip = SDL_FLIP_NONE;
		Player* player = (Player*)scene->get_game_object("player");
		player->getState();

		Vector_2D portal_center = _translation
			+ Vector_2D((float)_width / 2, (float)_height / 2);
		Vector_2D player_center = player->translation()
			+ Vector_2D((float)player->width() / 2, (float)player->height() / 2);

		float distance_to_player = (portal_center - player_center).magnitude();

		if (distance_to_player <= 30.f)
		{

			_to_be_destroyed = true;
		}
	}
	else {
		sword->set_translation(_translation + Vector_2D(0.0f, (float)_width / -200));
		if (flip_direction == 0)
		{
			_flip = SDL_FLIP_VERTICAL;
			flip_direction = 1;
		}
		else
		{
			_flip = SDL_FLIP_NONE;
			flip_direction = 0;
		}
	}

	
}

void Sword::setOriginalTranslation(Vector_2D translation)
{
	_originalTranslation = translation;
}
