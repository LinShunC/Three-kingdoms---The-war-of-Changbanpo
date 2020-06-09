#pragma once

#include "game_object.h"
#include <time.h>
#include <random>
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
	int _exit_time;

	Animated_Texture* _texture;
	int _change_direction_timer;
	std::minstd_rand0 _generator;

};