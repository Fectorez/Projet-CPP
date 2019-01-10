#include "pch.h"
#include "Character.h"
#include <iostream>

Character::Character(std::string textureFile, Direction direction, sf::Vector2u spriteSize, sf::Vector2f speed, float yDelta, float maxYSpeed, bool moving) :
	AnimatedObject(textureFile, spriteSize),
	m_direction(direction),
	m_speed(speed),
	m_moving(moving),
	m_maxYSpeed(maxYSpeed),
	m_yDelta(yDelta)
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

void Character::switchDirection()
{
	if ( m_direction == Direction::Left )
		m_direction = Direction::Right;
	else if ( m_direction == Direction::Right )
		m_direction = Direction::Left;
	else if ( m_direction == Direction::Up )
		m_direction = Direction::Down;
	else if ( m_direction == Direction::Down )
		m_direction = Direction::Up;
}

bool Character::reachesEndOfWindow() const
{
	return x() <= 0 || xRight() >= WINDOW_WIDTH;
}

bool Character::isMoving() const
{
	return m_moving;
}

void Character::setMoving(bool moving)
{
	m_moving = moving;
}

void Character::setJumping()
{
	if ( m_gravityState == Gravity::None )
	{
		m_gravityState = Gravity::Up;
		setAnim();
	}
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
			moveX(-m_speed.x);
			if ( x() < 0 && xRight() > 0 && ( !m_exitPlatform || m_exitPlatform != m_platform ) )
				setX(0);
		}
		else if ( m_direction == Direction::Right )
		{
			moveX(m_speed.x);
			if ( xRight() > WINDOW_WIDTH && m_exitPlatform != m_platform )
				setXRight(WINDOW_WIDTH);
		}
	}
	if ( m_gravityState == Gravity::Up )
	{
		moveY(-m_speed.y);
		m_speed.y -= m_yDelta;
		if ( m_speed.y <= 0 )
		{
			m_gravityState = Gravity::Down;
			m_speed.y = 0;
			m_maxJump = y();
		}
	}
	else if ( m_gravityState == Gravity::Down )
	{
		moveY(m_speed.y);
		m_speed.y += m_yDelta;
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

void Character::makeFall()
{
	if ( m_gravityState == Gravity::None )
	{
		m_gravityState = Gravity::Down;
		m_platform = nullptr;
		m_speed.y = 0.f;
	}
}

float Character::getMaxJump() const
{
	return m_maxJump;
}

void Character::resetMaxJump()
{
	m_maxJump = 0;
}

bool Character::isFalling() const
{
	return m_gravityState == Gravity::Down;
}

void Character::stopFall()
{
	m_gravityState = Gravity::None;
	setAnim();
	m_speed.y = m_maxYSpeed;
}

void Character::setExitPlatform(Platform * exitPlatform)
{
	m_exitPlatform = exitPlatform;
}
