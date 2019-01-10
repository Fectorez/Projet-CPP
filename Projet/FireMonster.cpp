#include "pch.h"
#include "FireMonster.h"


FireMonster::FireMonster():
	Character(FIRE_MONSTER_TEXTURE_FILE, Direction::Right, FIRE_MONSTER_SIZE, FIRE_MONSTER_SPEED, FIRE_MONSTER_Y_DELTA, FIRE_MONSTER_MAX_Y_SPEED ,true)
{
	setAnim();
}


FireMonster::~FireMonster()
{
}

void FireMonster::setAnim()
{
	if ( m_direction == Direction::Left )
		m_anim = FIRE_MONSTER_ANIM_LEFT;
	else
		m_anim = FIRE_MONSTER_ANIM_RIGHT;
}

void FireMonster::update()
{
	Character::update();
	if ( m_gravityState == Gravity::None )
		setJumping();
	if ( reachesEndOfWindow() )
	{
		switchDirection();
		setAnim();
	}
}

