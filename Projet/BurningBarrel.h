#pragma once
#include "AnimatedObject.h"
class BurningBarrel :
	public AnimatedObject
{
public:
	enum State{ Off, InFire };

public:
	BurningBarrel();
	~BurningBarrel();
	void setInFire();

private:
	State m_state;
};

