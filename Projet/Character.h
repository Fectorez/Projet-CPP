#pragma once

#include "SimpleObject.h"
#include "AnimatedObject.h"
#include "Platform.h"

class Character : public AnimatedObject
{
public:
	Character(std::string textureFile, Direction direction, sf::Vector2u spriteSize, sf::Vector2f speed, float yDelta = 0.f, float maxYSpeed = 0.f, bool moving = false);
	~Character();
	Direction getDirection() const;
	void setDirection(Direction direction);
	void switchDirection();
	bool reachesEndOfWindow() const;
	virtual void update();
	bool isMoving() const;
	void setMoving(bool moving);
	void setJumping();
	void moveX(float x);
	void moveY(float y);
	Platform* getPlatform() const;
	void setPlatform(Platform* platform);
	Gravity getGravityState() const;
	void makeFall();
	float getMaxJump() const;
	void resetMaxJump();
	bool isFalling() const;
	void stopFall();
	virtual void setAnim() = 0;
	void setConstantAnim(bool anim);

protected:
	virtual void updateSprite();

protected:
	Direction m_direction;
	sf::Vector2f m_speed;
	bool m_moving;
	bool m_constantAnim = false;
	Gravity m_gravityState = Gravity::None;
	Platform* m_platform = nullptr;
	float m_maxJump; // Point y le plus haut atteint lors du saut
	float m_maxYSpeed;
	float m_yDelta;
};
