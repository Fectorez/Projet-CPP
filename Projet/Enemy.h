#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy(std::string textureFile, Direction direction);
	~Enemy();
	void update();
};

