#include "pch.h"
#include "Barrel.h"


Barrel::Barrel(sf::Time timeToStart):
	Character(BARREL_TEXTURE_FILE, Direction::Right, 1, BARREL_SIZE),
	m_timeToStart(timeToStart),
	m_startClock()
{
	setAnim();
}


Barrel::~Barrel()
{
}

void Barrel::update()
{
	if ( !isMoving() && m_startClock.getElapsedTime() >= m_timeToStart )
	{
		setMoving(true);
		setDirection(Direction::Right);
	}
	Character::update();
}

void Barrel::setAnim()
{
	m_anim = BARREL_ANIM;
}

Gravity Barrel::getGravityState() const
{
	return m_gravityState;
}