#include "game_scene.h"
#include "dino.h"
#include "walking_dino.h"
#include "zombie.h"
#include "player.h"
#include "girl.h"
#include "portal_purple.h"
#include "portal_green.h"
#include "man.h"
#include "enemy.h"
#include "background.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{


	_background_color.r = 255;
	_background_color.b = 255;
	_background_color.g = 0;

	/*Game_Object* dino = new Dino("Dino");
	_game_objects[dino->id()] = dino;

	Game_Object* background = new Background("background");
	_game_objects[background->id()] = background;

	Game_Object* dino_walking = new Walking_Dino("Dino.Walking");
	_game_objects[dino_walking->id()] = dino_walking;


	//Game_Object* zombie = new Zombie("zombie");
	//_game_objects[zombie->id()] = zombie;

	Game_Object* player = new Player("player");
	_game_objects[player->id()] = player;

	Game_Object* girl = new Girl("girl");
	_game_objects[girl->id()] = girl;

	//Game_Object* man = new Man("man");
	//_game_objects[man->id()] = man;

	Game_Object* Exit = new Portal_Exit("Exit");
	_game_objects[Exit->id()] = Exit;

	Game_Object* Entry = new Portal_Entry("Entry");
	_game_objects[Entry->id()] = Entry;*/
	add_game_object(new Dino("Dino"));
	add_game_object(new Background("background"));
	add_game_object(new Walking_Dino("Dino.Walking"));
	add_game_object(new Player("player"));
	add_game_object(new Girl("girl"));
	add_game_object(new Portal_Exit("Exit"));
	add_game_object(new Portal_Entry("Entry"));
	add_game_object(new Enemy("Enemy"));
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window* window)
{
	Game_Object* player = get_game_object("player");
	Game_Object* background = get_game_object("background");
	background->set_translation(_camera_translation);
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	_camera_translation = Vector_2D(-w / 2.0f + player->width() / 2.f, -h / 1.2f + player->height() / 1.2f) + player->translation();

}