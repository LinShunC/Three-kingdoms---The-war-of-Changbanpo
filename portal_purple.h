#pragma once

#include "game_object.h"

class Portal_Exit : public Game_Object
{
public:
	Portal_Exit(std::string id);
	~Portal_Exit();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*,Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene) override;
};