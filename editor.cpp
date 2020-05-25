#include"editor.h"
#include"resource.h"
#include "player.h"


#include<SDL.h>
#include<SDL_syswm.h>
#include<iostream>

Editor::Editor(std::wstring window_name) 
{
	_window = FindWindow(NULL, window_name.c_str());
	if (_window == NULL)
	{
		std::cout << "Failed to find window. Window Name: " << window_name.c_str() << std::endl;
		exit(1);
	}
	_menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	if (_menu == NULL) 
	{
		std::cout << "Failed to create menu" << std::endl;
		exit(1);
	}
	BOOL set_menu_result = SetMenu(_window,_menu);
	if (set_menu_result == 0) 
	{
		std::cout << "Failed to set menu" << std::endl;
		exit(1);
	}

	Uint8 event_state_result = SDL_EventState(SDL_SYSWMEVENT,SDL_ENABLE);
	Uint8 event_state_success = SDL_DISABLE;
	if (event_state_result != event_state_success) 
	{
		std::cout << "Failed to enable Windows event state" << std::endl;
		exit(1);
	}
}
Editor::~Editor() {}

INT_PTR CALLBACK Dialog_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM ) 
{
	switch (Message) 
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON1:
				EndDialog(hwnd,IDOK);
				break;
			case IDC_BUTTON2:
				EndDialog(hwnd, IDOK);
				break;
			case IDC_BUTTON3:
				EndDialog(hwnd, IDOK);
				break;
			}
			break;
	   
		default:
			return false;
			
	}
	return TRUE;
}

void  Editor::update(Input* input,Scene* scene, Configuration* config)

{
	if (input->is_button_state(Input::Button::DECREASE_SPEED, Input::Button_State::PRESSED)) 
	{
		Player* player = (Player*)scene->get_game_object("player.idle");
		player->set_speed(player->speed() * 0.1f);
	}

	if (input->is_button_state(Input::Button::INCREASE_SPEED, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player.walking");
		player->set_speed(player->speed() * 2.0f);
	
	
	
	}
	if (input->is_button_state(Input::Button::CHANGETODINO, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player.walking");
		player->setID("Texture.Dino.Walking");

	}
	if (input->is_button_state(Input::Button::CHANGETOGIRL, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player");
		player->setID("girl");

	}
	if (input->is_button_state(Input::Button::CHANGETOMAN, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player");
		player->setID("man");

	}
	if (input->is_button_state(Input::Button::CHANGETOZOMBIE, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player");
		player->setID("zombie");

	}
	if (input->is_button_state(Input::Button::INCREASESIZE, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player");
		player->setSize();

	}
	if (input->is_button_state(Input::Button::RESET_SIZE, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player");
		player->resetSize();

	}
	if (input->is_button_state(Input::Button::RESET_SPEED, Input::Button_State::PRESSED))
	{
		Player* player = (Player*)scene->get_game_object("player");
		player->resetSpeed();

	}
	if (input->is_button_state(Input::Button::SHOW_CREDITS, Input::Button_State::PRESSED))
	{
		
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), _window, Dialog_Proc);
	
	}
	if (input->is_button_state(Input::Button::DEBUG_SHOW_IDS, Input::Button_State::PRESSED))
	{
		config->should_display_ids = !config->should_display_ids;
	
	}
	if (input->is_button_state(Input::Button::DEBUG_SHOW_LOCATION, Input::Button_State::PRESSED))
	{
		config->should_display_loc = !config->should_display_loc;

	}
	if (input->is_button_state(Input::Button::DEBUG_SHOW_TEXTUREID, Input::Button_State::PRESSED))
	{
		config->should_display_tid = !config->should_display_tid;

	}
	if (input->is_button_state(Input::Button::DEBUG_SHOW_COLLIDER, Input::Button_State::PRESSED))
	{
		config->should_display_colliders = !config->should_display_colliders;

	}
	if (input->is_button_state(Input::Button::SHOW_COMPANY, Input::Button_State::PRESSED))
	{

		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), _window, Dialog_Proc);

	}
	if (input->is_button_state(Input::Button::SHOW_PAUSE, Input::Button_State::PRESSED))
	{

		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG3), _window, Dialog_Proc);

	}
	

}