#pragma once

#include "SimpleObject.h"
#include "AnimatedObject.h"

class Character : public AnimatedObject
{
public:
	Character(std::string textureFile, Direction direction = Direction::Right, int speed = 1, bool moving = false, sf::Vector2i anim = { 0,0 }, sf::Vector2i nbAnim = { 3,3 }, sf::Vector2i spriteSize = { 32,32 });
	~Character();
	Direction getDirection() const;
	void setDirection(Direction direction);
	virtual void update();
	bool isMoving() const;
	void setMoving(bool moving);

protected:
	virtual void updateSprite();

protected:
	Direction m_direction;
	int m_speed;
	bool m_moving;
};
