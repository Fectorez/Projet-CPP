#pragma once
#include "SimpleObject.h"
class Ladder :
	public SimpleObject
{
public:
	Ladder();
	void build(SimpleObject* pPartTop, SimpleObject* pPartBottom, Direction direction); // direction = où mettre l'échelle par rapport au bloc ? à sa gauche ou à sa droite ?
	~Ladder();
};

