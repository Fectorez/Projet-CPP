#pragma once

#include "PlatformPart.h"

class Platform : public Entity
{
public:
	Platform(sf::Vector2i extremity, Direction direction);
	~Platform();
	void draw(sf::RenderWindow& window);
	void update();
	std::vector<PlatformPart*> getParts() const;

private:
	std::vector<PlatformPart*> m_parts;
};

