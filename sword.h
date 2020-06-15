#pragma once

#include "game_object.h"

class Sword : public Game_Object
{
public:
	Sword(std::string id);
	~Sword();


	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	void setOriginalTranslation(Vector_2D translation);

private:
	int flip_direction;
	Vector_2D _originalTranslation;
};