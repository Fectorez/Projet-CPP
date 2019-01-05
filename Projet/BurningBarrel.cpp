#include "pch.h"
#include "BurningBarrel.h"


BurningBarrel::BurningBarrel():
	AnimatedObject(BURNING_BARREL_TEXTURE_FILE, BURNING_BARREL_SIZE, BURNING_BARRIL_ANIM_OFF),
	m_state(Off)
{
}


BurningBarrel::~BurningBarrel()
{
}

void BurningBarrel::setInFire()
{
	if ( m_state == Off )
	{
		m_state = InFire;
		m_anim = BURNING_BARRIL_ANIM;
	}
}
