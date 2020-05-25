#pragma once

#include "game_object.h"

class Enemy : public Game_Object
{
public:
	Enemy(std::string id);
	~Enemy();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
	void setID(string id);
private:
	bool _has_spawned_another = false;

};