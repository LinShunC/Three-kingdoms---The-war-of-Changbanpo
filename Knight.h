#pragma once

#include "game_object.h"
#include <time.h>
#include <random>

class Knight : public Game_Object
{
public:
	Knight(std::string id);
	~Knight();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
	void setID(string id);
private:
	Animated_Texture* _texture;
	int _change_direction_timer;
	std::minstd_rand0 _generator;

};