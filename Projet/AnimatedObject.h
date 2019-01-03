#pragma once

#include "SimpleObject.h"

class AnimatedObject :
	public SimpleObject
{
public:
	AnimatedObject(std::string textureFile, sf::Vector2u spriteSize, Anim anim = { 0,0,0 });
	~AnimatedObject();
	virtual void update();
	
protected:
	virtual void updateSprite();
	virtual void setTextureAnim();

protected:
	static const sf::Time TimePerAnim;
	sf::Clock m_clock;
	sf::Vector2u m_spriteSize;
	Anim m_anim;
};

