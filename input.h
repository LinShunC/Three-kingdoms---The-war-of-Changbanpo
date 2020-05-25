#pragma once

#include <map>

class Input
{
public:
	Input();
	~Input();

	enum class  Button
	{
		QUIT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SLIDE,
		ATTACK,
        PAUSE,
		INCREASE_SPEED,
		DECREASE_SPEED,
		SHOW_CREDITS,
		DEBUG_SHOW_IDS,
		SHOW_COMPANY,
		SHOW_PAUSE,
		DEBUG_SHOW_LOCATION,
		DEBUG_SHOW_TEXTUREID,
		DEBUG_SHOW_COLLIDER,
		CHANGETODINO,
		INCREASESIZE,
		RESET_SIZE,
		RESET_SPEED,
		CHANGETOGIRL,
		CHANGETOMAN,
		CHANGETOZOMBIE,


	};

	enum class Button_State
	{
		PRESSED,
		DOWN,
		RELEASED,
		UP,

		
	};
	void get_input();
	bool is_button_state(Button type, Button_State state);
private:
	std::map<Button, Button_State> _button_state;

};