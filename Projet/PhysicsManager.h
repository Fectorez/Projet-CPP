#pragma once

#include "Collision.h"
#include "Player.h"
#include "Platform.h"

namespace PhysicsManager
{
	bool collide(sf::Sprite& obj1, sf::Sprite& obj2);
	bool collide(Player& player, PlatformPart* ppart);
	void manageMarioClimb(Player& player);
	void manageMarioDescent(Player& player);
	void manageMarioJump(Player& player, Platform& platform);
};

