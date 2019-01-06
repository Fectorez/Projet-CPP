#include "pch.h"
#include "Barrel.h"


Barrel::Barrel(std::string textureFile, sf::Time timeToStart):
	Character(textureFile, Direction::Right, BARREL_SPEED, BARREL_SIZE),
	m_timeToStart(timeToStart),
	m_startClock()
{
	setAnim();
}

Barrel::Barrel(sf::Time timeToStart):
	Barrel(BARREL_TEXTURE_FILE,timeToStart)
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
	if ( xRight() <= 0 )
		m_left = true;
}

void Barrel::setAnim()
{
	m_anim = BARREL_ANIM;
}

Gravity Barrel::getGravityState() const
{
	return m_gravityState;
}

TYPE Barrel::getType() const
{
	return WOODEN;
}

bool Barrel::isLeft() const
{
	return m_left;
}