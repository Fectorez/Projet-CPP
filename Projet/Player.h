#pragma once

#include "Character.h"
#include "Platform.h"
#include "Ladder.h"

class Player : public Character
{
public:
	Player(std::string textureFile);
	~Player();
	void update();
	void updateSprite();
	void setJumping();
	bool isGoingUp() const;
	bool isFalling() const;
	void makeFall();
	void stopFall();
	Ladder* getLadder() const;
	void setLadder(Ladder* ladder);
	float getMaxJump() const;
	void resetMaxJump();
	void setClimbingLadder(Ladder* ladder, Direction direction);

private:
	void setAnim();
	void climbUpLadder();
	void climbOffLadder();
	void stopClimbLadder();

private:
	static const float MAX_JUMP_SPEED;
	float m_jumpSpeed = MAX_JUMP_SPEED;
	Ladder* m_ladder = nullptr;

	float m_maxJump; // Point y le plus haut atteint lors du saut
};

