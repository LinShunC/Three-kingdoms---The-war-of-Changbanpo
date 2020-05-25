#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>
#include "asset.h"
using namespace std;
class Texture :public Asset
{
public:
	Texture(string id, string path, SDL_Renderer* renderer);
	~Texture();
	SDL_Texture* data();
	virtual	void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip);
private:
	SDL_Texture* _data;
};

