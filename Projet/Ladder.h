#pragma once
#include "SimpleObject.h"
class Ladder :
	public SimpleObject
{
public:
	Ladder();
	void build(SimpleObject* pPartTop, SimpleObject* pPartBottom, Direction direction); // direction = o� mettre l'�chelle par rapport au bloc ? � sa gauche ou � sa droite ?
	~Ladder();
};

