#pragma once

#include "background.h"

Background::Background(std::string id)
	: Game_Object(id, "background")
{
	_translation = Vector_2D(0, 0);

	_width = 800;
	_height = 800;
}
Background::~Background()
{
}
void Background::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}
