#include "game_scene.h"
#include "dino.h"
#include "walking_dino.h"

#include "player.h"
#include "girl.h"
#include "portal_purple.h"
#include "portal_green.h"

#include "enemy.h"
#include "background.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{


	_background_color.r = 255;
	_background_color.b = 255;
	_background_color.g = 0;

	add_game_object(new Background("background"));

	add_game_object(new Player("player"));
	add_game_object(new Portal_Exit("Exit"));
	//add_game_object(new Portal_Entry("Entry"));
	//add_game_object(new Enemy("Enemy"));
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window* window)
{
	Game_Object* player = get_game_object("player");
	Game_Object* background = get_game_object("background");
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	_camera_translation = Vector_2D(-w / 2.0f + player->width() / 2.f, -h / 1.2f + player->height() / 1.2f) + player->translation();
	background->set_translation(_camera_translation);
	/*Game_Object* exit = get_game_object("Exit");
	exit->set_translation(Vector_2D(w / 5.0f  , -h / 3.0f)  + player->translation());*/


}