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
	m_sprite.setTexture(m_texture);
}

SimpleObject::SimpleObject(std::string textureFile, sf::IntRect textureRect):
	SimpleObject(textureFile)
{
	m_sprite.setTextureRect(textureRect);
}


SimpleObject::~SimpleObject()
{
}

void SimpleObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Vector2f SimpleObject::getPosition() const
{
	return m_sprite.getPosition();
}

float SimpleObject::x() const
{
	return getPosition().x;
}

float SimpleObject::y() const
{
	return getPosition().y;
}


float SimpleObject::xRight() const
{
	return getPosition().x + getSize().x;
}

float SimpleObject::yBottom() const
{
	return getPosition().y + getSize().y;
}

void SimpleObject::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void SimpleObject::setX(float x)
{
	m_sprite.setPosition(x, m_sprite.getPosition().y);
}

void SimpleObject::setY(float y)
{
	m_sprite.setPosition(m_sprite.getPosition().x, y);
}

void SimpleObject::setXRight(float x)
{
	setX(x+-width());
}

void SimpleObject::setYBottom(float y)
{
	setY(y-height());
}

sf::Vector2i SimpleObject::getSize() const
{
	sf::IntRect rect = m_sprite.getTextureRect();
	return sf::Vector2i(rect.width,rect.height);
}

int SimpleObject::width() const
{
	return getSize().x;
}

int SimpleObject::height() const
{
	return getSize().y;
}

sf::Sprite SimpleObject::getSprite() const
{
	return m_sprite;
}

void SimpleObject::moveX(float x)
{
	m_sprite.move(x, 0);
}

void SimpleObject::moveY(float y)
{
	m_sprite.move(0, y);
}
