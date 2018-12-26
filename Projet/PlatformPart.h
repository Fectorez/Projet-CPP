#pragma once

#include "SimpleObject.h"

class PlatformPart :
	public SimpleObject
{
public:
	PlatformPart();
	~PlatformPart();
	void update();
};

