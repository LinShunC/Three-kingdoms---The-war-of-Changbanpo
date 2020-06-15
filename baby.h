#pragma once

#include "game_object.h"

class Baby : public Game_Object
{
public:
	Baby(std::string id);
	~Baby();


	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};