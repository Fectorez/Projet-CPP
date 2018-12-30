#include "pch.h"
#include "Platform.h"


Platform::Platform(sf::Vector2f extremity, Direction direction, Position position):
	m_direction(direction)
{
	m_parts = {};
	float y = extremity.y;
	float x = extremity.x;
	if ( direction == Direction::Left )
		m_xRight = x + PLATFORM_SIZE_X;
	else
		m_xLeft = x;
	while ( position != Position::Peach &&  x >= 0 && x < WINDOW_HEIGHT || position == Position::Peach && x < extremity.x + PLATFORM_SIZE_X*3 )
	{
		SimpleObject* part = new SimpleObject(PLATFORM_TEXTURE_FILE);
		part->setPosition(x,y);
		m_parts.push_back(part);
		if ( position == Position::None || position == Position::Bottom && x >= WINDOW_WIDTH*0.4 || position == Position::Top && x > WINDOW_WIDTH/2 )
			y -= 1.5;
		if ( direction == Direction::Left )
			x -= PLATFORM_SIZE_X;
		else
			x += PLATFORM_SIZE_X;
	}
	if ( direction == Direction::Left )
		m_xLeft = x + PLATFORM_SIZE_X;
	else
		m_xRight = x - PLATFORM_SIZE_Y;
}

Platform::~Platform()
{
	for ( SimpleObject* const& ppart : m_parts )
		delete ppart;
}

void Platform::draw(sf::RenderWindow & window)
{
	for ( SimpleObject *part : m_parts )
		part->draw(window);
}

void Platform::update()
{
}

std::vector<SimpleObject*> Platform::getParts() const
{
	return m_parts;
}

Direction Platform::getDirection() const
{
	return m_direction;
}

float Platform::xLeft() const
{
	return m_xLeft;
}

float Platform::xRight() const
{
	return m_xRight;
}
