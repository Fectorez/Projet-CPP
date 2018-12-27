#pragma once

#include "PlatformPart.h"

class Platform : public Entity
{
public:
	Platform(sf::Vector2i extremity, Direction direction, Position position = Position::None);
	~Platform();
	void draw(sf::RenderWindow& window);
	void update();
	std::vector<PlatformPart*> getParts() const;
	Direction getDirection() const;
	float xLeft() const;
	float xRight() const;

private:
	std::vector<PlatformPart*> m_parts;
	Direction m_direction; // vers le haut
	float m_xLeft;
	float m_xRight;
};

