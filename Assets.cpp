#include "Assets.h"

#include <iostream>

Assets::Assets(SDL_Renderer* renderer)
{
	Texture* dino_texture = new Texture("Texture.Dino", "Assets/dino.png", renderer);
	_asset[dino_texture->id()] = dino_texture;


	Texture* background = new Texture("background", "Assets/background.jpeg", renderer);
	_asset[background->id()] = background;

	Texture* colider = new Texture("Texture.Colider","Assets/collider.png",renderer);
	_asset[colider->id()] = colider;

		



	{const int frame_count_player = 10;
	const Uint32 frame_duration_milliseconds_player = 370;

	Animated_Texture* player =
		new Animated_Texture("player.dieing", "Assets/player.dieing.png", renderer,
			frame_count_player, frame_duration_milliseconds_player);
	_asset[player->id()] = player;
	}

	{const int frame_count_player = 10;
	const Uint32 frame_duration_milliseconds_player = 370;

	Animated_Texture* Enemy =
		new Animated_Texture("enemy.run", "Assets/enemy_run.png", renderer,
			frame_count_player, frame_duration_milliseconds_player);
	_asset[Enemy->id()] = Enemy;
	}

	{const int frame_count_player = 10;
	const Uint32 frame_duration_milliseconds_player = 100;

	Animated_Texture* Enemy =
		new Animated_Texture("enemy.dieing", "Assets/enemy_dead.png", renderer,
			frame_count_player, frame_duration_milliseconds_player);
	_asset[Enemy->id()] = Enemy;
	}
	{const int frame_count_player = 10;
	const Uint32 frame_duration_milliseconds_player = 100;

	Animated_Texture* player =
		new Animated_Texture("player.walking", "Assets/player.walking.png", renderer,
			frame_count_player, frame_duration_milliseconds_player);
	_asset[player->id()] = player;
	}

	
	{
		const int frame_count_player = 10;
		const Uint32 frame_duration_milliseconds_player = 100;

		Animated_Texture* player =
			new Animated_Texture("player.idle", "Assets/player.idle.png", renderer,
				frame_count_player, frame_duration_milliseconds_player);
		_asset[player->id()] = player;
	}
	{
		const int frame_count_player = 10;
		const Uint32 frame_duration_milliseconds_player = 38;

		Animated_Texture* player =
			new Animated_Texture("player.attack", "Assets/player.attack.png", renderer,
				frame_count_player, frame_duration_milliseconds_player);
		_asset[player->id()] = player;
	}
	{
		const int frame_count_player = 10;
		const Uint32 frame_duration_milliseconds_player = 100;

		Animated_Texture* player =
			new Animated_Texture("player.slide", "Assets/player.slide.png", renderer,
				frame_count_player, frame_duration_milliseconds_player);
		_asset[player->id()] = player;
	}


	{const int frame_count = 10;
	const Uint32 frame_duration_milliseconds = 200;

	Animated_Texture* walking_dino_texture =
		new Animated_Texture("Texture.Dino.Walking", "Assets/dino.walking.png", renderer,
			frame_count, frame_duration_milliseconds);
	_asset[walking_dino_texture->id()] = walking_dino_texture;
	}

	{const int frame_count = 8;
	const Uint32 frame_duration_milliseconds = 100;

	Animated_Texture* portal_green_texture =
		new Animated_Texture("Texture.portal.green", "Assets/portal.green.png", renderer,
			frame_count, frame_duration_milliseconds);
	_asset[portal_green_texture->id()] = portal_green_texture;
	}
	{const int frame_count = 8;
	const Uint32 frame_duration_milliseconds = 100;

	Animated_Texture* portal_purple_texture =
		new Animated_Texture("Texture.portal.purple", "Assets/portal.purple.png", renderer,
			frame_count, frame_duration_milliseconds);
	_asset[portal_purple_texture->id()] = portal_purple_texture;
	}



	const int frame_count_zombie = 6;
	const Uint32 frame_duration_milliseconds_zombie = 300;
	Animated_Texture* zombie = new Animated_Texture("zombie", "Assets/zombie.png", renderer,
		frame_count_zombie, frame_duration_milliseconds_zombie);
	_asset[zombie->id()] = zombie;

	const int frame_count_girl = 4;
	const Uint32 frame_duration_milliseconds_girl = 300;
	Animated_Texture* girl = new Animated_Texture("girl", "Assets/girl.png", renderer,
		frame_count_girl, frame_duration_milliseconds_girl);
	_asset[girl->id()] = girl;

	const int frame_count_man = 4;
	const Uint32 frame_duration_milliseconds_man = 300;
	Animated_Texture* man = new Animated_Texture("man", "Assets/man.png", renderer,
		frame_count_man, frame_duration_milliseconds_man);
	_asset[man->id()] = man;



	/*



	const int frame_count_run = 6;
	const Uint32 frame_duration_milliseconds_run = 200;
	Animated_Texture* run = new Animated_Texture("run", "Assets/run.png", renderer,
		frame_count_run, frame_duration_milliseconds_run);
	_asset[run->id()] = run;

		const int frame_count_coin = 6;
	const Uint32 frame_duration_milliseconds_coin = 300;
	Animated_Texture* coin = new Animated_Texture("coin", "Assets/coin.png", renderer,
		frame_count_coin, frame_duration_milliseconds_coin);
	_asset[coin->id()] = coin;

	*/

	{
		Sound* sound = new Sound("Sound.Music", "Assets/background.wav");
		_asset[sound->id()] = sound;
		Mix_PlayChannel(0, sound->data(), -1);

	}

	{
		Sound* walking = new Sound("Sound.Walking", "Assets/walking.wav");
		_asset[walking->id()] = walking;
		

	}

	{
		Sound* running = new Sound("Sound.Slide", "Assets/Slide.wav");
		_asset[running->id()] = running;
		

	}
	{
		Sound* idle = new Sound("Sound.Idle", "Assets/idle.wav");
		_asset[idle->id()] = idle;
		Mix_PlayChannel(1, idle->data(), -1);
	}
	{
		Sound* Die = new Sound("Sound.Die", "Assets/die.wav");
		_asset[Die->id()] = Die;
		
	}
	{
		Sound* Attack = new Sound("Sound.Attack", "Assets/attack.wav");
		_asset[Attack->id()] = Attack;

	}

}

Assets::~Assets()
{

}



Asset* Assets::get_asset(std::string id)
{
	if (_asset.find(id) == _asset.end())
	{
		std::cout << "Attempted to find an animated texture that was not loaded. ID: " << id << std::endl;
		exit(1);
	}

	return _asset[id];
}