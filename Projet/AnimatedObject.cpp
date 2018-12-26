#include "pch.h"
#include "AnimatedObject.h"

const sf::Time AnimatedObject::TimePerAnim = sf::seconds(TIME_PER_ANIM);

AnimatedObject::AnimatedObject(std::string textureFile, sf::Vector2i firstAnim, sf::Vector2i nbAnim, sf::Vector2i spriteSize):
	SimpleObject(textureFile),
	m_anim(firstAnim),
	m_nbAnim(nbAnim),
	m_spriteSize(spriteSize),
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
	m_anim.x++;
	if ( m_anim.x == m_nbAnim.x )
		m_anim.x = 0;
	setTextureAnim();
}

void AnimatedObject::setTextureAnim()
{
	m_sprite.setTextureRect(sf::IntRect(m_anim.x*m_spriteSize.x, m_anim.y*m_spriteSize.y, m_spriteSize.x, m_spriteSize.y));
}
