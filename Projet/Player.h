#pragma once

#include "Character.h"
#include "Platform.h"

class Player : public Character
{
public:
	Player(std::string textureFile);
	~Player();
	void update();
	void setJumping();
	bool isGoingUp() const;
	bool isGoingDown() const;
	void makeFall();
	void stopFall();
	Platform* getPlatform() const;
	void setPlatform(Platform* platform);
	Gravity getGravityState() const;

private:
	static const float MAX_JUMP_SPEED;
	Gravity m_gravityState = Gravity::None;
	float m_jumpSpeed = MAX_JUMP_SPEED;
	Platform* m_platform;
};

