#include "pch.h"
#include "Platform.h"


Platform::Platform(sf::Vector2i extremity, Direction direction)
{
	m_parts = {};
	int y = extremity.y;
	int x = extremity.x;
	while ( x >= 0 && x < WINDOW_HEIGHT )
	{
		PlatformPart* part = new PlatformPart();
		part->setPosition((float)x,(float)y);
		m_parts.push_back(part);
		y--;
		if ( direction == Direction::Left )
			x -= TEXTURE_SIZE;
		else
			x += TEXTURE_SIZE;
	}
}

Platform::~Platform()
{
	for ( PlatformPart* const& ppart : m_parts )
		delete ppart;
}

void Platform::draw(sf::RenderWindow & window)
{
	for ( PlatformPart *part : m_parts )
		part->draw(window);
}

void Platform::update()
{
}

std::vector<PlatformPart*> Platform::getParts() const
{
	return m_parts;
}