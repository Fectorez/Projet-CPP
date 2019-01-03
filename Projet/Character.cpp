#include "pch.h"
#include "Character.h"
#include <iostream>

Character::Character(std::string textureFile, Direction direction, float speed, sf::Vector2u spriteSize, bool moving) :
	AnimatedObject(textureFile, spriteSize),
	m_direction(direction),
	m_speed(speed),
	m_moving(moving)
{
}


Character::~Character()
{
}

Direction Character::getDirection() const
{
	return m_direction;
}

void Character::setDirection(Direction direction)
{
	if ( m_direction != direction )
	{
		m_direction = direction;
		setAnim();
	}
}

bool Character::isMoving() const
{
	return m_moving;
}

void Character::setMoving(bool moving)
{
	m_moving = moving;
}

void Character::moveX(float x)
{
	m_sprite.move(x, 0.f);
}

void Character::moveY(float y)
{
	m_sprite.move(0.f, y);
}

void Character::update()
{
	if ( m_moving )
	{
		if ( m_direction == Direction::Left )
		{
			moveX(-m_speed);
			if ( x() < 0 )
				setX(0);
		}
		else if ( m_direction == Direction::Right )
		{
			moveX(m_speed);
			if ( xRight() > WINDOW_WIDTH )
				setXRight(WINDOW_WIDTH);
		}
	}
	AnimatedObject::update();
}

void Character::updateSprite()
{
	if ( !m_moving || ++m_anim.x == m_anim.nb )
		m_anim.x = 0;
	setTextureAnim();
}

Platform * Character::getPlatform() const
{
	return m_platform;
}

void Character::setPlatform(Platform * platform)
{
	m_platform = platform;
}

Gravity Character::getGravityState() const
{
	return m_gravityState;
}
