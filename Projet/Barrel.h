#pragma once
#include "Character.h"
#include "Platform.h"

class Barrel :
	public Character
{
public:
	Barrel(sf::Time timeToStart);
	~Barrel();
	void update();
	void setAnim();
	Gravity getGravityState() const;

private:
	sf::Time m_timeToStart;
	sf::Clock m_startClock;
};

