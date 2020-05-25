#pragma once


#include "game_object.h"

class Background : public Game_Object
{
public:
	Background(std::string id);
	~Background();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
};