#include "pch.h"
#include "PhysicsManager.h"

namespace PhysicsManager
{
	bool PhysicsManager::collide(sf::Sprite& obj1, sf::Sprite& obj2)
	{
		sf::FloatRect rect1 = obj1.getGlobalBounds();
		sf::FloatRect rect2 = obj2.getGlobalBounds();
		return rect1.intersects(rect2);
	}

	bool PhysicsManager::collide(Player & player, PlatformPart * ppart)
	{
		sf::Sprite s1 = ppart->getSprite();
		sf::Sprite s2 = player.getSprite();
		return collide(s1,s2);
	}

	void PhysicsManager::manageMarioClimb(Player & player)
	{
		if ( !player.isMoving() || player.getGravityState() != Gravity::None )
			return;
		bool climbsLeft = player.getDirection() == Direction::Left && player.getPlatform()->getDirection() == Direction::Left;
		bool climbsRight = player.getDirection() == Direction::Right && player.getPlatform()->getDirection() == Direction::Right;
		if ( climbsLeft || climbsRight )
			for ( PlatformPart* ppart : player.getPlatform()->getParts() )
				if ( collide(player, ppart) )
					player.setY(ppart->y() - player.getSize().y );
	}

	void PhysicsManager::manageMarioDescent(Player & player)
	{
		if ( !player.isMoving() || player.getGravityState() != Gravity::None )
			return;
		bool descendsLeft = player.getDirection() == Direction::Left && player.getPlatform()->getDirection() == Direction::Right;
		bool descendsRight = player.getDirection() == Direction::Right && player.getPlatform()->getDirection() == Direction::Left;
		if ( !descendsLeft && !descendsRight )
			return;
		// Sort de sa plateforme
		if ( descendsLeft && player.xRight() < player.getPlatform()->xLeft() || descendsRight && player.x() > player.getPlatform()->xRight() )
		{
			player.makeFall();
			return;
		}
		for ( PlatformPart* ppart : player.getPlatform()->getParts() )
		{
			bool ownPPart = descendsRight && player.x() >= ppart->x() && player.xRight() <= ppart->xRight();
			ownPPart = ownPPart || descendsLeft && player.xRight() <= ppart->xRight() && player.x() >= ppart->x();
			if ( ownPPart && player.yBottom() + 1 < ppart->y() )
				player.setY(ppart->y() - player.getSize().y);
		}
	}

	void PhysicsManager::manageMarioJump(Player & player, Platform & platform)
	{
		std::vector<PlatformPart*> pparts = platform.getParts();
		for ( SimpleObject* const& ppart : pparts )
		{
			if ( Collision::BoundingBoxTest(player.getSprite(), ppart->getSprite()) )
			{
				sf::Vector2f pos = player.getPosition();
				if ( player.isGoingUp() )
				{
					std::cout << "up" << std::endl;
					player.setPosition(pos.x,ppart->getPosition().y+TEXTURE_SIZE+1);
					player.makeFall();
				}
				else if ( player.isGoingDown() )
				{
					std::cout << "down" << std::endl;
					player.setPosition(pos.x,ppart->getPosition().y-TEXTURE_SIZE-1);
					player.stopFall();
				}
				else if ( player.getDirection() == Direction::Left )
				{
					std::cout << "left" << std::endl;
					player.setPosition(ppart->getPosition().x + TEXTURE_SIZE+1, pos.y);
					player.setMoving(false);
				}
				else
				{
					std::cout << "right" << std::endl;
					player.setPosition(ppart->getPosition().x - TEXTURE_SIZE-1, pos.y);
					player.setMoving(false);
				}
			}
		}
	}
}