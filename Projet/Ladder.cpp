#include "pch.h"
#include "Ladder.h"

Ladder::Ladder(): SimpleObject(LADDER_TEXTURE_FILE) 
{}

void Ladder::build(SimpleObject* pPartTop, SimpleObject* pPartBottom, Direction direction)
{
	float newHeight = pPartBottom->y() - pPartTop->y();
	m_sprite.setTextureRect(sf::IntRect(0,height()-newHeight,width(), newHeight));
	float xPosition = pPartTop->x();
	if ( direction == Direction::Right )
		xPosition = pPartTop->xRight() - width();
	setPosition(xPosition,pPartTop->y());
}


Ladder::~Ladder()
{
}
