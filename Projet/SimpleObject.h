#pragma once

#include "pch.h"
#include "Entity.h"

class SimpleObject : public Entity
{
public:
	SimpleObject(std::string textureFile);
	~SimpleObject();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition()const;
	float x() const;
	float y() const;
	float xRight() const;
	float yBottom() const;
	void setPosition(float x, float y);
	void setX(float x);
	void setY(float y);
	sf::Vector2i getSize() const;
	sf::Sprite getSprite() const;

	virtual void update() = 0;

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};