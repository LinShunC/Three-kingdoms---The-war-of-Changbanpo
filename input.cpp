#include "input.h"
#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_syswm.h>
#include"resource.h"

Input::Input() 
{
}Input::~Input()
{
}

bool Input::is_button_state(Button type, Button_State state) 
{
	
	if (_button_state.find(type) == _button_state.end()) 
	{
		if (state == Button_State::UP) 
		{
			return true;
		}
		else 
	{
			return false;
		}
	}
	return _button_state.find(type)->second == state;
}

void Input::get_input() 
{
	_button_state[Button::INCREASE_SPEED] = Button_State::UP;
	_button_state[Button::CHANGETODINO] = Button_State::UP;
	_button_state[Button::CHANGETOGIRL] = Button_State::UP;
	_button_state[Button::CHANGETOMAN] = Button_State::UP;
	_button_state[Button::CHANGETOZOMBIE] = Button_State::UP;
	_button_state[Button::INCREASESIZE] = Button_State::UP;
	_button_state[Button::RESET_SIZE] = Button_State::UP;
	_button_state[Button::RESET_SPEED] = Button_State::UP;
	_button_state[Button::DECREASE_SPEED] = Button_State::UP;
	_button_state[Button::SHOW_CREDITS] = Button_State::UP;
	_button_state[Button::DEBUG_SHOW_IDS] = Button_State::UP;
	_button_state[Button::DEBUG_SHOW_LOCATION] = Button_State::UP;
	_button_state[Button::DEBUG_SHOW_TEXTUREID] = Button_State::UP;
	_button_state[Button::DEBUG_SHOW_COLLIDER] = Button_State::UP;
	_button_state[Button::SHOW_COMPANY] = Button_State::UP;
	_button_state[Button::SHOW_PAUSE] = Button_State::UP;
	
	for (auto button_state : _button_state) 
	{
		if (button_state.second == Button_State::PRESSED)
		{
			_button_state[button_state.first] = Button_State::DOWN;
		}
		else if (button_state.second == Button_State::RELEASED)
		{
			_button_state[button_state.first] = Button_State::UP;
		}
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
		case SDL_QUIT :
			_button_state[Button::QUIT] = Button_State::PRESSED;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) 
			{
			case SDL_SCANCODE_W:
				if (!is_button_state(Button::UP, Button_State::DOWN))
				{
					_button_state[Button::UP] = Button_State::PRESSED;
				}
				break;
			case SDL_SCANCODE_A:
				if (!is_button_state(Button::LEFT, Button_State::DOWN))
				{
					_button_state[Button::LEFT] = Button_State::PRESSED;
				}
				break;
			case SDL_SCANCODE_S:
				if (!is_button_state(Button::DOWN, Button_State::DOWN))
				{
					_button_state[Button::DOWN] = Button_State::PRESSED;
				}
				break;
			case SDL_SCANCODE_D:
				if (!is_button_state(Button::RIGHT, Button_State::DOWN))
				{
					_button_state[Button::RIGHT] = Button_State::PRESSED;
				}
				break;
			case SDL_SCANCODE_LSHIFT:
				if (!is_button_state(Button::SLIDE, Button_State::DOWN))
				{
					_button_state[Button::SLIDE] = Button_State::PRESSED;
				}
				break;
			case SDL_SCANCODE_H:
				if (!is_button_state(Button::ATTACK, Button_State::DOWN))
				{
					_button_state[Button::ATTACK] = Button_State::PRESSED;
				}
				break;
			case SDL_SCANCODE_ESCAPE:
				if (!is_button_state(Button::PAUSE, Button_State::DOWN))
				{
					_button_state[Button::PAUSE] = Button_State::PRESSED;
				}
				break;
			}
			break;
			
		case SDL_KEYUP:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				
					_button_state[Button::UP] = Button_State::RELEASED;
				
				break;
			case SDL_SCANCODE_A:
				
					_button_state[Button::LEFT] = Button_State::RELEASED;
				
				break;
			case SDL_SCANCODE_S:
				
					_button_state[Button::DOWN] = Button_State::RELEASED;
				
				break;
			case SDL_SCANCODE_D:
				
					_button_state[Button::RIGHT] = Button_State::RELEASED;
				
				break;
			case SDL_SCANCODE_LSHIFT:
				_button_state[Button::SLIDE] = Button_State::RELEASED;
				break;
			case SDL_SCANCODE_H:
				_button_state[Button::ATTACK] = Button_State::RELEASED;
				break;
			case SDL_SCANCODE_ESCAPE:
				_button_state[Button::PAUSE] = Button_State::RELEASED;
				break;

			}
			break;
		case SDL_SYSWMEVENT:
			if (event.syswm.msg->msg.win.wParam == ID_FILE_EXIT)
			{
				_button_state[Button::QUIT] = Button_State::PRESSED;
			}
			else if (event.syswm.msg->msg.win.wParam == ID_PLAYER_INCRESEDSPEED)
			{
				_button_state[Button::INCREASE_SPEED] = Button_State::PRESSED;
	
			}
			else if (event.syswm.msg->msg.win.wParam == ID_PLAYER_CHANGETODINO)
			{
				_button_state[Button::CHANGETODINO] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_CHARACTERS_CHANGETOGIRL)
			{
				_button_state[Button::CHANGETOGIRL] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_CHARACTERS_CHANGETOMAN)
			{
				_button_state[Button::CHANGETOMAN] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_CHARACTERS_CHANGETOZOMBIE)
			{
				_button_state[Button::CHANGETOZOMBIE] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_RESET_SIZE)
			{
				_button_state[Button::RESET_SIZE] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_RESET_SPEED)
			{
				_button_state[Button::RESET_SPEED] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_PLAYER_INCREASESIZE)
			{
				_button_state[Button::INCREASESIZE] = Button_State::PRESSED;

			}


			
			else if (event.syswm.msg->msg.win.wParam == ID_PLAYER_DECREASESPEED) {

				_button_state[Button::DECREASE_SPEED] = Button_State::PRESSED;
			}
			else if (event.syswm.msg->msg.win.wParam == ID_CREDITS_DEVELOPERS) {

				_button_state[Button::SHOW_CREDITS] = Button_State::PRESSED;
				std::cout << "pressed" << std::endl;
			}
			else if (event.syswm.msg->msg.win.wParam == ID_CREDITS_COMPANY) {

				_button_state[Button::SHOW_COMPANY] = Button_State::PRESSED;
				
			}
			else if (event.syswm.msg->msg.win.wParam == ID_CREDITS_PAUSE) {

				_button_state[Button::SHOW_PAUSE] = Button_State::PRESSED;

			}
			else if (event.syswm.msg->msg.win.wParam == ID_DEBUG_TOGGLEDISPLAYID)
			{
				_button_state[Button::DEBUG_SHOW_IDS] = Button_State::PRESSED;
			}
			else if (event.syswm.msg->msg.win.wParam == ID_DEBUG_TOGGLEDISPLAYLOCATION)
			{
				_button_state[Button::DEBUG_SHOW_LOCATION] = Button_State::PRESSED;
			}
			else if (event.syswm.msg->msg.win.wParam == ID_DEBUG_TOGGLEDISPLAYTEXTUREID)
			{
				_button_state[Button::DEBUG_SHOW_TEXTUREID] = Button_State::PRESSED;
			}
			else if (event.syswm.msg->msg.win.wParam ==  ID_DEBUG_TOGGLEDISPLAYCOLLIDER)
			{
				_button_state[Button::DEBUG_SHOW_COLLIDER] = Button_State::PRESSED;
			}

			break;
			
		}
		
	
	}
}