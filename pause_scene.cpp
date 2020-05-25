#include "pause_scene.h"


Pause_Scene::Pause_Scene()
	: Scene("Pause")
{

	_background_color.r = 255;
	_background_color.b = 0;
	_background_color.g = 0;
}

Pause_Scene::~Pause_Scene()
{
}

void Pause_Scene::update(SDL_Window* )
{
	
}