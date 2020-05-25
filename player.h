#pragma once

#include "game_object.h"
#include "assets.h"
#include <stack>

class Player : public Game_Object
{
public:
	Player(std::string id);
	~Player();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene) override;

	void set_speed(float speed);
	void setID(string id);
	void setSize();
	void resetSpeed();
	void resetSize();
	float speed();
	void DistanceToEnemy(float distance);

	enum class State
	{
		Idle,
		Walking,
		slide,
		Dieing,
		Attack,
	};
	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);
	string getState();
	void setDieState();
private:
	float _speed;
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);
	std::stack<State> _state;

	float distance_to_enemy;
	int _current_run_timer_ms;
	int _next_run_time_ms;



};