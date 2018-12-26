#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(std::string textureFile, Direction direction):
	Character(textureFile, direction, 1, true, { 0,2 }, { 4,4 }, { 24,32 })
{
	m_sprite.setPosition(50, 50);
}


Enemy::~Enemy()
{
}

void Enemy::update()
{
	Character::update();
	if ( m_sprite.getPosition().x < 0 )
	{
		m_direction = Direction::Right;
	}
	else if ( m_sprite.getPosition().x + m_spriteSize.x > WINDOW_WIDTH )
	{
		m_direction = Direction::Left;
	}
}
