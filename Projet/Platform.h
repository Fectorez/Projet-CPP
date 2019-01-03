#pragma once

#include "SimpleObject.h"

class Platform : public Entity
{
public:
	Platform(sf::Vector2f extremity, Direction direction, Position position = Position::None);
	~Platform();
	void draw(sf::RenderWindow& window);
	void update();
	std::vector<SimpleObject*> getParts() const;
	Direction getDirection() const;
	float xLeft() const;
	float xRight() const;
	float yTop() const;
	float yBottom() const;

private:
	std::vector<SimpleObject*> m_parts;
	Direction m_direction; // vers le haut
	float m_xLeft;
	float m_xRight;
	float m_yTop;
	float m_yBottom;
};

