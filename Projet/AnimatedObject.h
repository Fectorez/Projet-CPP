#pragma once

#include "SimpleObject.h"

class AnimatedObject :
	public SimpleObject
{
public:
	AnimatedObject(std::string textureFile, sf::Vector2i firstAnim, sf::Vector2i nbAnim, sf::Vector2i spriteSize);
	~AnimatedObject();
	virtual void update();
	
protected:
	virtual void updateSprite();
	virtual void setTextureAnim();

protected:
	static const sf::Time TimePerAnim;
	sf::Vector2i m_anim;
	sf::Clock m_clock;
	sf::Vector2i m_nbAnim;
	sf::Vector2i m_spriteSize;
};

