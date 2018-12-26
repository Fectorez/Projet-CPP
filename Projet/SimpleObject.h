#pragma once

#include "pch.h"
#include "Entity.h"

class SimpleObject : public Entity
{
public:
	SimpleObject(std::string textureFile);
	~SimpleObject();
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y);
	sf::Sprite getSprite() const;

	virtual void update() = 0;

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};