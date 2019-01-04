#include "pch.h"
#include "BarrelOfOil.h"


BarrelOfOil::BarrelOfOil():
	AnimatedObject(BARREL_OIL_TEXTURE_FILE, BARREL_OIL_SIZE, BARRIL_OIL_ANIM),
	m_state(Off)
{
}


BarrelOfOil::~BarrelOfOil()
{
}

void BarrelOfOil::setInFire()
{
	if ( m_state == Off )
	{
		m_state = InFire;
		m_anim = BARRIL_OIL_ANIM_FIRE;
	}
}
