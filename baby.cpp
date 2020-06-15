#pragma once

#include "baby.h"
#include "player.h"

Baby::Baby(std::string id)
	: Game_Object(id, "Baby")
{

	_height = 100;
	_width = 100;
	_translation = Vector_2D(350, 350);
	_collider.set_radius(_width / 10.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));
}

Baby::~Baby()
{
}
void Baby::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	Player* player = (Player*)scene->get_game_object("player");

	Vector_2D portal_center = _translation
		+ Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation()
		+ Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_center - player_center).magnitude();

	if (distance_to_player < 80.0f && player->getState() != "Dieing")
	{

		_player_message = true;
		player->set_win();

	}
	else 
	{
		_player_message = false;
	}

}


