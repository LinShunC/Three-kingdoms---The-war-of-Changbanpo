#pragma once
#pragma once

#include "scene.h"


class Pause_Scene : public Scene
{
public:
	Pause_Scene();
	~Pause_Scene();


	virtual void update(SDL_Window* window) override;


};