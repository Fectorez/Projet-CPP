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

	bool PhysicsManager::collide(Player & player, SimpleObject * obj2)
	{
		sf::Sprite s1 = player.getSprite();
		sf::Sprite s2 = obj2->getSprite();
		return collide(s1,s2);
	}

	void PhysicsManager::manageMarioClimb(Player & player)
	{
		if ( !player.isMoving() || player.getGravityState() != Gravity::None )
			return;
		bool climbsLeft = player.getDirection() == Direction::Left && player.getPlatform()->getDirection() == Direction::Left;
		bool climbsRight = player.getDirection() == Direction::Right && player.getPlatform()->getDirection() == Direction::Right;
		if ( climbsLeft || climbsRight )
			for ( SimpleObject* ppart : player.getPlatform()->getParts() )
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
		for ( SimpleObject* ppart : player.getPlatform()->getParts() )
		{
			bool ownPPart = descendsRight && player.x() >= ppart->x() && player.xRight() <= ppart->xRight();
			ownPPart = ownPPart || descendsLeft && player.xRight() <= ppart->xRight() && player.x() >= ppart->x();
			if ( ownPPart && player.yBottom() + 1 < ppart->y() )
				player.setY(ppart->y() - player.getSize().y);
		}
	}

	// � modifier
	void PhysicsManager::manageMarioJump(Player & player, Platform & platform)
	{
		std::vector<SimpleObject*> pparts = platform.getParts();
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
				else if ( player.isFalling() )
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
	void PhysicsManager::manageMarioFall(Player & player, std::vector<Platform*> platforms)
	{
		if ( !player.isFalling() )
			return;
		for ( auto platform : platforms )
			for ( auto pPart : platform->getParts() )
				if ( collide(player, pPart) && player.yBottom() <= pPart->yBottom() && pPart->y() - player.height() > player.getMaxJump() )
				{
					player.resetMaxJump();
					player.setPlatform(platform);
					player.stopFall();
					player.setY(pPart->y()-player.height());
					return;
				}
	}

	void playerDoesntMove(Player & player)
	{
		player.setMoving(false);
	}

	void playerTriesToGoLeft(Player & player)
	{
		if ( player.getDirection() != Direction::Up && player.getDirection() != Direction::Down )
		{
			player.setDirection(Direction::Left);
			player.setMoving(true);
		}
	}

	void playerTriesToGoRight(Player & player)
	{
		if ( player.getDirection() != Direction::Up && player.getDirection() != Direction::Down )
		{
			player.setDirection(Direction::Right);
			player.setMoving(true);
		}
	}

	void PhysicsManager::playerTriesToClimbLadder(Player& player, std::vector<Ladder*> ladders)
	{
		if ( player.getLadder() != nullptr )
		{
			player.setDirection(Direction::Up);
			player.setMoving(true);
		}
		else
		{
			for ( Ladder* ladder : ladders )
				if ( collide(player, ladder) )
					player.setClimbingLadder(ladder,Direction::Up);
		}
	}
	void playerTriesToClimbOffLadder(Player & player, std::vector<Ladder*> ladders)
	{
		if ( player.getLadder() == nullptr )
		{
			for ( Ladder* ladder : ladders )
			{
				if ( player.x() >= ladder->x() && player.x() <= ladder->xRight() || player.xRight() >= ladder->x() && player.xRight() <= ladder->xRight() )
					if ( player.yBottom() == ladder->y() )
					{
						player.setClimbingLadder(ladder, Direction::Down);
						return;
					}
			}
		}
		else
		{
			player.setDirection(Direction::Down);
			player.setMoving(true);
		}
	}
}