#pragma once
#include "Character.h"
#include "Platform.h"

class Barrel :
	public Character
{
public:
	Barrel(std::string textureFile, sf::Time timeToStart);
	Barrel(sf::Time timeToStart);
	~Barrel();
	void update();
	void setAnim();
	Gravity getGravityState() const;

	bool isLeft() const;

private:
	sf::Time m_timeToStart;
	sf::Clock m_startClock;
	bool m_left = false;
};

