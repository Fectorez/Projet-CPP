#include "pch.h"
#include "DonkeyKong.h"


DonkeyKong::DonkeyKong():
	AnimatedObject(DK_TEXTURE_FILE,DK_SIZE,DK_ANIM),
	m_timePerAction(sf::seconds(1))
{
}


DonkeyKong::~DonkeyKong()
{
}

void DonkeyKong::update()
{
	if ( m_clock.getElapsedTime() > m_timePerAction )
	{
		m_clock.restart();
		setNextState();
		updateSprite();
		doAction();
	}
}

bool DonkeyKong::placesBarrel()
{
	if ( m_placesBarrel )
	{
		m_placesBarrel = false;
		return true;
	}
	return false;
}

sf::Time DonkeyKong::getTimePerAction() const
{
	return m_timePerAction;
}

void DonkeyKong::updateSprite()
{
	m_anim.x = (int)m_state;
	setTextureAnim();
}

void DonkeyKong::setNextState()
{
	int intState = ((int)m_state) + 1;
	if ( (DKState)intState == DKState::StopBlueBarrel )
		intState++;
	if ( intState == m_anim.nb )
		intState = 0;
	m_state = (DKState)intState;
}

void DonkeyKong::doAction()
{
	switch ( m_state )
	{
	case DKState::Stop :
		break;
	case DKState::Left :
		break;
	case DKState::StopBarrel:
		break;
	case DKState::StopBlueBarrel:
		break;
	case DKState::Right:
		m_placesBarrel = true;
		break;
	}
}