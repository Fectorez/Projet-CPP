#include "pch.h"
#include "SimpleObject.h"
#include <iostream>


SimpleObject::SimpleObject(std::string textureFile)
{
	if ( !m_texture.loadFromFile(textureFile) )
	{
		std::cerr << "Erreur chargement texture" << std::endl;
		exit(1);
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}


SimpleObject::~SimpleObject()
{
}

void SimpleObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void SimpleObject::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

sf::Sprite SimpleObject::getSprite() const
{
	return m_sprite;
}
