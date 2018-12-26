#pragma once

#include "Character.h"

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


private:
	static const float MAX_JUMP_SPEED;
	JumpState m_jumpState = JumpState::None;
	float m_jumpSpeed = MAX_JUMP_SPEED;
};

