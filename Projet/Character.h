#pragma once

#include "SimpleObject.h"
#include "AnimatedObject.h"

class Character : public AnimatedObject
{
public:
	Character(std::string textureFile, Direction direction, float speed, sf::Vector2i spriteSize, bool moving = false);
	~Character();
	Direction getDirection() const;
	void setDirection(Direction direction);
	virtual void update();
	bool isMoving() const;
	void setMoving(bool moving);
	void moveX(float x);
	void moveY(float y);
	virtual void setAnim() = 0;

protected:
	virtual void updateSprite();

protected:
	Direction m_direction;
	float m_speed;
	bool m_moving;
};
