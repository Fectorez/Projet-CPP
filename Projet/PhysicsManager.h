#pragma once

#include "pch.h"

class Player;
class Platform;
class Ladder;
class Character;
class Barrel;
class SimpleObject;

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	static bool collide(sf::Sprite& obj1, sf::Sprite& obj2);
	static bool collide(Character* obj1, SimpleObject * obj2);
	void addAll(Player* player, std::vector<Ladder*>* ladders, std::vector<Platform*>* platforms, std::vector<Barrel*>* barrels);
	void manageMarioClimb();
	void manageMarioDescent();
	void manageBarrelsDescent();
	//void manageMarioJump();
	void manageMarioFall();
	void playerDoesntMove();
	void playerTriesToGoLeft();
	void playerTriesToGoRight();
	void playerTriesToClimbLadder();
	void playerTriesToClimbOffLadder();

private:
	void manageDescent(Character* obj);

private:
	Player* m_player;
	std::vector<Ladder*>* m_ladders;
	std::vector<Platform*>* m_platforms;
	std::vector<Barrel*>* m_barrels;
};

