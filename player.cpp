#pragma once

#include "player.h"
#include "input.h"

int time_when_hit = 0;

Player::Player(std::string id)
	: Game_Object(id, "player.idle")
{
	
	_speed = 0.2f;
	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));
	_state.push(State::Idle);

	_width = 90;
	_height = 90;
	_current_run_timer_ms = 0;
	_next_run_time_ms = 0;

}
Player::~Player()
{
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config,Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Player::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene)
{
	State state = _state.top();


	Game_Object* player = (Game_Object*)scene->get_game_object("girl");
	Vector_2D portal_center = _translation
		+ Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation()
		+ Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_center - player_center).magnitude();

	_next_run_time_ms -= milliseconds_to_simulate;
	_current_run_timer_ms -= milliseconds_to_simulate;
	

	switch (_state.top())
	{
	case State::Idle:
		if (input->is_button_state(Input::Button::SLIDE, Input::Button_State::DOWN) && _velocity.magnitude() > 0.0f && _next_run_time_ms <0)
		{
			push_state(State::slide, assets);
		}
		else if (_velocity.magnitude() > 0.0f)
		{
			push_state(State::Walking, assets);
		}
		else if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::PRESSED))
		{
			push_state(State::Attack, assets);
		}
		 if (distance_to_enemy <	10.0f)
		{
			push_state(State::Dieing, assets);
		}
	
		break;
	case State::Walking:

		if (_velocity.magnitude() == 0.0f)
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::SLIDE, Input::Button_State::PRESSED) && _next_run_time_ms < 0)
		{
			push_state(State::slide, assets);
		}
		else if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::PRESSED))
		{
			push_state(State::Attack, assets);
		}
		else if (distance_to_enemy < 10.0f)
		{
			push_state(State::Dieing, assets);
		}
		break;
	case State::slide:
		if (_velocity.magnitude() == 0.0f)
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::SLIDE, Input::Button_State::RELEASED))
		{
			pop_state(assets);
		}

		else if (distance_to_enemy < 10.0f)
		{
			push_state(State::Dieing, assets);
		}
		else if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::PRESSED))
		{
			push_state(State::Attack, assets);
		}
		else if (_current_run_timer_ms <=0) 
		{
			pop_state(assets);
		}
	
		break;
	case State::Dieing:
		
		// if (distance_to_player > 50.0f && _velocity.magnitude() == 0.0f)
	//	{
	//		pop_state(assets);
	//	}
		  if (distance_to_player > 50.0f && input->is_button_state(Input::Button::SLIDE, Input::Button_State::DOWN) && _velocity.magnitude() > 0.0f)
		 {
			 push_state(State::slide, assets);
		 }
		 else if (distance_to_player > 50.0f && _velocity.magnitude() > 0.0f)
		 {
			 push_state(State::Walking, assets);
		 }
		break;

	case State::Attack:

		if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::RELEASED))
		{
			pop_state(assets);
		}
		else if ( input->is_button_state(Input::Button::SLIDE, Input::Button_State::DOWN) && _velocity.magnitude() > 
			0.0f && _next_run_time_ms < 0)
		{
			push_state(State::slide, assets);
		}
		else if ( _velocity.magnitude() > 0.0f)
		{
			push_state(State::Walking, assets);
		}
		break;
	
	}
	_velocity = Vector_2D(0, 0);

	if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(1.0f, 0);
	}
	if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(-1.0f, 0);
	}
	if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, -1.0f);
	}
	if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, 1.0f);
	}
	if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::PRESSED) && state!= State::Attack)
	{
		time_when_hit = 370;
		push_state(State::Attack, assets);
	}
	if (state == State::Attack )
	{
		time_when_hit -= milliseconds_to_simulate;
		if (time_when_hit < 0) {
			pop_state(assets);
		}
	}

	_velocity.normalize();
	_velocity.scale(_speed);

	

}
void Player::set_speed(float speed)
{
	_speed = speed;
}

float Player::speed()
{
	return _speed;
}
void Player::setID(string id)
{
	_texture_id = id;
}
void Player::setSize()
{
	_width = _width * 2;
	_height = _height * 2;
}
void Player::resetSize()
{
	_width = 100;
	_height = 100;
}
void Player::resetSpeed()
{
	_speed = 0.1f;
}


void Player::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}
void Player::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player::handle_enter_state(State state, Assets* assets)
{
	const int channel = 1;
	
	
	switch (state)
	{
		
	case State::Idle:
	{
		_texture_id = "player.idle";


	
	Sound* idle = (Sound*)assets->get_asset("Sound.Idle");
	Mix_PlayChannel(channel, idle->data(), -1);

	break;
	}

	case State::Walking:
	{	_texture_id = "player.walking";
	_speed = 0.15f;


	Sound* walking = (Sound*)assets->get_asset("Sound.Walking");
	Mix_PlayChannel(channel, walking->data(), -1);
	break;
	}
	
	case State::slide:

	{
	_texture_id = "player.slide";
	_speed = 0.3f;

	_current_run_timer_ms = 2000;

	Sound* Slide = (Sound*)assets->get_asset("Sound.Slide");
	Mix_PlayChannel(channel, Slide->data(), -1);
	break; 
	}
	case State::Dieing:
	
	{
		_texture_id = "player.dieing";
		_speed = 0.3f;


	
		Sound* Die = (Sound*)assets->get_asset("Sound.Die");


		Mix_PlayChannel(channel, Die->data(), -1);

		break;
	}
	case State::Attack:

	{
		_texture_id = "player.attack";
		_speed = 0.3f;



		Sound* Attack = (Sound*)assets->get_asset("Sound.Attack");


		Mix_PlayChannel(channel, Attack->data(), -1);

		break;
	}

	}
}



void Player::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
	case State::Idle: {
		
		Mix_HaltChannel(1);
		break;
	}
		
	case State::Walking:
	{
		
		Mix_HaltChannel(1);
		break;
	}
	case State::slide:
	{
		_next_run_time_ms = 2000;
		Mix_HaltChannel(1);
		break;
	}
	case State::Dieing:
	{
	
		Mix_HaltChannel(1);
		break;
	}
	case State::Attack:
	{

		Mix_HaltChannel(1);
		break;
	}
	}
}

string Player::getState() 
{
	State state = _state.top();
	switch (state)
	{
	case State::Attack:
	{

		return "attack";
		break;
	}

	}
	return "";
}
void Player::setDieState()
{
	_state.top() = State::Dieing;
}

void Player::DistanceToEnemy(float distance)
{
	distance_to_enemy = distance;
}