#include "pch.h"
#include "BlueBarrel.h"


BlueBarrel::BlueBarrel(sf::Time timeToStart):
	Barrel(BLUE_BARREL_TEXTURE_FILE,timeToStart)
{
}


BlueBarrel::~BlueBarrel()
{
}

TYPE BlueBarrel::getType() const
{
	return BLUE;
}
