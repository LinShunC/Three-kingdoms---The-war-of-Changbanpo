#include <iostream>
#include <chrono>
#include <thread>

#include "engine.h"
#include "assets.h"
#include "input.h"
#include "game_scene.h"
#include "editor.h"
#include"configuration.h"
#include "pause_scene.h"
#include <stack>
int main(void)
{
	Configuration* config = new Configuration();
	Engine* engine = new Engine("Game",  config);
	Assets* assets = new Assets(engine->renderer());
	Input* input = new Input();

	Editor* editor = new Editor(L"Game");

	std::stack<Scene*> scenes;
	scenes.push(new Game_Scene());

	const Uint32 milliseconds_per_seconds = 1000;
	const Uint32 frames_per_second = 60;
	const Uint32 frame_time_ms = milliseconds_per_seconds / frames_per_second;

	Uint32 frame_start_time_ms = 0;
	//int time_when_hit = 0;
	Uint32 frame_end_time_ms = frame_time_ms;
	while (!input->is_button_state(Input::Button::QUIT,Input::Button_State::PRESSED))
	{
		Uint32 previous_frame_duration = frame_end_time_ms - frame_start_time_ms;
		frame_start_time_ms = SDL_GetTicks();

		
		scenes.top()->update(engine->window());
		input->get_input();


		if (input->is_button_state(Input::Button::PAUSE,Input::Button_State::PRESSED)) 
		{
			const bool is_paused = scenes.top()->id() == "Pause";
			if (is_paused) 
			{
				Pause_Scene* pause_scene = (Pause_Scene*)scenes.top();
				scenes.pop();
				delete pause_scene;
			}
			else 
			{
				scenes.push(new Pause_Scene);
			}

		}

		/*if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::PRESSED))
		{
			time_when_hit = 1000;
		}
		if (time_when_hit>=0)
		{
			time_when_hit -= previous_frame_duration;
		}*/


		editor->update(input, scenes.top(), config);
		if (input->is_button_state(Input::Button::UP,Input::Button_State::PRESSED)) 
		{
			std::cout << "UP pressed" << endl;
		}
		else if (input->is_button_state(Input::Button::DOWN, Input::Button_State::PRESSED))
		{
			std::cout << "down pressed" << endl;
		}
		else if (input->is_button_state(Input::Button::LEFT, Input::Button_State::PRESSED))
		{
			std::cout << "LEFT pressed" << endl;
		}
		else if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::PRESSED))
		{
			std::cout << "RIGHT pressed" << endl;
		}


		engine->simulate(previous_frame_duration, assets, scenes.top(),input, config);

		const Uint32 current_time_ms = SDL_GetTicks();
		const Uint32 frame_duration_ms = current_time_ms - frame_start_time_ms;
		if (frame_duration_ms < frame_time_ms)
		{
			const Uint32 time_to_sleep_for = frame_time_ms - frame_duration_ms;
			std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep_for));
		}

		frame_end_time_ms = SDL_GetTicks();

		//std::cout << frame_end_time_ms - frame_start_time_ms << std::endl;
	}

	return 0;
}