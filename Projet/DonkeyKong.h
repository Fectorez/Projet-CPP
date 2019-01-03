#pragma once
#include "AnimatedObject.h"
class DonkeyKong :
	public AnimatedObject
{
public:
	DonkeyKong();
	~DonkeyKong();
	void update();
	bool placesBarrel();
	sf::Time getTimePerAction() const;

private:
	void setNextState();
	void doAction();
	void updateSprite();

private:
	DKState m_state;
	sf::Time m_timePerAction;
	bool m_placesBarrel = false;
};

