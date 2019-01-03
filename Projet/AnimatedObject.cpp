#include "pch.h"
#include "AnimatedObject.h"

const sf::Time AnimatedObject::TimePerAnim = sf::seconds(TIME_PER_ANIM);

AnimatedObject::AnimatedObject(std::string textureFile, sf::Vector2u spriteSize, Anim anim):
	SimpleObject(textureFile),
	m_spriteSize(spriteSize),
	m_anim(anim),
	m_clock()
{
	setTextureAnim();
}


AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::update()
{
	if ( m_clock.getElapsedTime() > TimePerAnim )
	{
		updateSprite();
		m_clock.restart();
	}
}

void AnimatedObject::updateSprite()
{
	if ( ++m_anim.x == m_anim.nb )
		m_anim.x = 0;
	setTextureAnim();
}

void AnimatedObject::setTextureAnim()
{
	m_sprite.setTextureRect(sf::IntRect(m_anim.x*m_spriteSize.x, m_anim.y*m_spriteSize.y, m_spriteSize.x, m_spriteSize.y));
}
