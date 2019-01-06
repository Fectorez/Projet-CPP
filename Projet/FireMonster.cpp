#include "pch.h"
#include "FireMonster.h"


FireMonster::FireMonster():
	Character(FIRE_MONSTER_TEXTURE_FILE, Direction::Right, FIRE_MONSTER_SPEED, FIRE_MONSTER_SIZE, FIRE_MONSTER_Y_SPEED, true)
{
	setAnim();
}


FireMonster::~FireMonster()
{
}

void FireMonster::setAnim()
{
	m_anim = FIRE_MONSTER_ANIM;
}
