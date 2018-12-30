#pragma once

#include "Collision.h"
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"

namespace PhysicsManager
{
	bool collide(sf::Sprite& obj1, sf::Sprite& obj2);
	bool collide(Player & player, SimpleObject * obj2);
	void manageMarioClimb(Player& player);
	void manageMarioDescent(Player& player);
	void manageMarioJump(Player& player, Platform& platform);
	void manageMarioFall(Player& player, std::vector<Platform*> platforms);
	void playerDoesntMove(Player& player);
	void playerTriesToGoLeft(Player& player);
	void playerTriesToGoRight(Player& player);
	void playerTriesToClimbLadder(Player& player, std::vector<Ladder*> ladders);
	void playerTriesToClimbOffLadder(Player& player, std::vector<Ladder*> ladders);
};

