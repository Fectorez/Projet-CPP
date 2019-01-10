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
	bool isGoingUp() const;
	Ladder* getLadder() const;
	void setLadder(Ladder* ladder);
	void setClimbingLadder(Ladder* ladder, Direction direction);

private:
	void setAnim();
	void climbUpLadder();
	void climbOffLadder();
	void stopClimbLadder();

private:
	Ladder* m_ladder = nullptr;
};

