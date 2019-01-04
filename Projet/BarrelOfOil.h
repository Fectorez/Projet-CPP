#pragma once
#include "AnimatedObject.h"
class BarrelOfOil :
	public AnimatedObject
{
public:
	enum State{ Off, InFire };

public:
	BarrelOfOil();
	~BarrelOfOil();
	void setInFire();

private:
	State m_state;
};

