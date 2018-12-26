#include "pch.h"
#include "Character.h"
#include <iostream>



Character::Character(std::string textureFile, Direction direction, int speed, bool moving, sf::Vector2i firstAnim, sf::Vector2i nbAnim, sf::Vector2i spriteSize) :
	AnimatedObject(textureFile, firstAnim,nbAnim,spriteSize),
	m_direction(direction),
	m_speed(speed),
	m_moving(moving)
{
}


Character::~Character()
{
}

Direction Character::getDirection() const
{
	return m_direction;
}

void Character::setDirection(Direction direction)
{
	m_direction = direction;
}

bool Character::isMoving() const
{
	return m_moving;
}

void Character::setMoving(bool moving)
{
	m_moving = moving;
}

void Character::update()
{
	if ( m_moving )
		m_sprite.move(float(m_speed*(int)m_direction), 0.f);
	AnimatedObject::update();
}

void Character::updateSprite()
{
	if ( m_moving )
	{
		m_anim.y = (m_direction == Direction::Left ? 1 : 2);
		m_anim.x++;
	}
	if ( m_anim.x == m_nbAnim.x || !m_moving )
		m_anim.x = 0;
	AnimatedObject::setTextureAnim();
}