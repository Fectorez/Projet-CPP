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
	void setHammer(bool);
	bool hasHammer();

private:
	void setAnim();
	void climbUpLadder();
	void climbOffLadder();
	void stopClimbLadder();
	void setTextureAnim();

private:
	Ladder* m_ladder = nullptr;
	sf::Vector2u m_hammerSpriteSize;
	unsigned m_blockSizeY = MARIO_TEXTURE_BLOCK_SIZE_Y;
	HammerState m_hammerState;
	bool m_hasHammer = false;
	sf::Clock clock;
	sf::Time elapsed;
};

