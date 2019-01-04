#include "pch.h"
#include "Character.h"
#include <iostream>

Character::Character(std::string textureFile, Direction direction, float speed, sf::Vector2u spriteSize, float ySpeed, bool moving) :
	AnimatedObject(textureFile, spriteSize),
	m_direction(direction),
	m_speed(speed),
	m_ySpeed(ySpeed),
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
			if ( x() < 0 && xRight() > 0 && ( !m_exitPlatform || m_exitPlatform != m_platform ) )
				setX(0);
		}
		else if ( m_direction == Direction::Right )
		{
			moveX(m_speed);
			if ( xRight() > WINDOW_WIDTH && m_exitPlatform != m_platform )
				setXRight(WINDOW_WIDTH);
		}
	}
	if ( m_gravityState == Gravity::Up )
	{
		moveY(-m_ySpeed);
		m_ySpeed -= JUMP_SPEED;
		if ( m_ySpeed <= 0 )
		{
			m_gravityState = Gravity::Down;
			m_ySpeed = 0;
			m_maxJump = y();
		}
	}
	else if ( m_gravityState == Gravity::Down )
	{
		moveY(m_ySpeed);
		m_ySpeed += 0.1f;
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
		m_ySpeed = 0.f;
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
	m_ySpeed = MAX_JUMP;
}

void Character::setExitPlatform(Platform * exitPlatform)
{
	m_exitPlatform = exitPlatform;
}
