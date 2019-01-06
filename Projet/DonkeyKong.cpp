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

bool DonkeyKong::placesBlueBarrel()
{
	if ( m_placesBlueBarrel )
	{
		m_placesBlueBarrel = false;
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
	if ( m_state == DKState::RightBlueBarrel )
		m_anim.x = (int)DKState::Right;
	setTextureAnim();
}

void DonkeyKong::setNextState()
{
	int alea;
	bool blueBarrel;
	switch ( m_state )
	{
	case DKState::Stop :
		m_state = DKState::Left;
		break;
	case DKState::Left:
		alea = rand() % 100 + 1;
		blueBarrel = alea < PROBA_BLUE_BARREL * 100;
		if ( blueBarrel )
			m_state = DKState::StopBlueBarrel;
		else
			m_state = DKState::StopBarrel;
		break;
	case DKState::StopBarrel :
		m_state = DKState::Right;
		break;
	case DKState::StopBlueBarrel:
		m_state = DKState::RightBlueBarrel;
		break;
	case DKState::Right:
		m_state = DKState::Stop;
	case DKState::RightBlueBarrel:
		m_state = DKState::Stop;
	}
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
	case DKState::RightBlueBarrel:
		m_placesBlueBarrel = true;
		break;
	}
}