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
	static bool collide_1D_strict(sf::Vector2f a, sf::Vector2f b);
	static bool collide_1D_strict(sf::Vector2f a, sf::Vector2f b, float percentOfA); // Collision de segment à <percent>% (Ex: {1,3} et {2,30} -> 50% de A)
	void addAll(Player* player, std::vector<Ladder*>* ladders, std::vector<Platform*>* platforms, std::vector<Barrel*>* barrels);
	void manageMarioClimb();
	void manageMarioDescent();
	void manageBarrelsDescent();
	//void manageMarioJump();
	void manageMarioFall();
	void manageBarrelsFall();
	void playerDoesntMove();
	void playerTriesToGoLeft();
	void playerTriesToGoRight();
	void playerTriesToClimbLadder();
	void playerTriesToClimbOffLadder();

private:
	void manageDescent(Character* obj);
	void manageFall(Character* obj, bool setBottomDirection = false);

private:
	Player* m_player;
	std::vector<Ladder*>* m_ladders;
	std::vector<Platform*>* m_platforms;
	std::vector<Barrel*>* m_barrels;
};

