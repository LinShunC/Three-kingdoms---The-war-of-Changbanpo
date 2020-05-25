#pragma once

#include "game_object.h"

class Man : public Game_Object
{
public:
	Man(std::string id);
	~Man();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer,Configuration* config,Scene* scene) override;
};