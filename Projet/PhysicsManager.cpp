#include "pch.h"
#include "PhysicsManager.h"

#include "Collision.h"
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"
#include "Character.h"
#include "Barrel.h"

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

// Static
bool PhysicsManager::collide(sf::Sprite& obj1, sf::Sprite& obj2)
{
	sf::FloatRect rect1 = obj1.getGlobalBounds();
	sf::FloatRect rect2 = obj2.getGlobalBounds();
	return rect1.intersects(rect2);
}

bool PhysicsManager::collide(Character* obj1, SimpleObject * obj2)
{
	sf::Sprite s1 = obj1->getSprite();
	sf::Sprite s2 = obj2->getSprite();
	return collide(s1,s2);
}

bool PhysicsManager::collide_1D_strict(sf::Vector2f a, sf::Vector2f b)
{
	bool aLeft_bRight = a.y > b.x && a.x < b.x;
	bool aRight_bLeft = b.y > a.x && b.x < a.x;
	bool a_in_b = a.x > b.x && a.y < b.y;
	bool b_in_a = b.x > a.x && b.y < a.y;
	return aLeft_bRight || aRight_bLeft || a_in_b || b_in_a;
}

bool PhysicsManager::collide_1D_strict(sf::Vector2f a, sf::Vector2f b, float percentOfA)
{
	float commonPart = -1.f;

	bool aLeft_bRight = a.y > b.x && a.x < b.x;
	if ( aLeft_bRight )
		commonPart = a.y - b.x;

	bool aRight_bLeft = b.y > a.x && b.x < a.x;
	if ( aRight_bLeft )
		commonPart = b.y - a.x;

	bool a_in_b = a.x > b.x && a.y < b.y;
	if ( a_in_b )
		return true;

	bool b_in_a = b.x > a.x && b.y < a.y;
	if ( b_in_a )
		return true;

	if ( commonPart != -1.f )
	{
		float commonPartPercent = commonPart * 100 / (a.y - a.x);
		return commonPartPercent >= percentOfA;
	}

	return false;
}



void PhysicsManager::addAll(Player * player, std::vector<Ladder*>* ladders, std::vector<Platform*>* platforms, std::vector<Barrel*>* barrels)
{
	m_player = player;
	m_ladders = ladders;
	m_platforms = platforms;
	m_barrels = barrels;
	m_player->setManager(this);
	for ( Ladder* ladder : *m_ladders )
		ladder->setManager(this);
	for ( Platform* platform : *m_platforms )
		platform->setManager(this);
	for ( Barrel* barrel : *m_barrels )
		barrel->setManager(this);
}



void PhysicsManager::manageMarioClimb()
{
	if ( !m_player->isMoving() || m_player->getGravityState() != Gravity::None )
		return;
	bool climbsLeft = m_player->getDirection() == Direction::Left && m_player->getPlatform()->getDirection() == Direction::Left;
	bool climbsRight = m_player->getDirection() == Direction::Right && m_player->getPlatform()->getDirection() == Direction::Right;
	if ( climbsLeft || climbsRight )
		for ( SimpleObject* ppart : m_player->getPlatform()->getParts() )
			if ( collide(m_player,ppart) )
				m_player->setY(ppart->y() - m_player->height() );
}

void PhysicsManager::manageMarioDescent()
{
	manageDescent(m_player);
}

void PhysicsManager::manageBarrelsDescent()
{
	for ( Barrel* barrel : *m_barrels )
		manageDescent(barrel);
}

/*
void PhysicsManager::manageMarioJump(Player & player, Platform & platform)
{
	std::vector<SimpleObject*> pparts = platform.getParts();
	for ( SimpleObject* const& ppart : pparts )
	{
		if ( Collision::BoundingBoxTest(m_player->getSprite(), ppart->getSprite()) )
		{
			sf::Vector2f pos = m_player->getPosition();
			if ( m_player->isGoingUp() )
			{
				std::cout << "up" << std::endl;
				m_player->setPosition(pos.x,ppart->getPosition().y+TEXTURE_SIZE+1);
				m_player->makeFall();
			}
			else if ( m_player->isFalling() )
			{
				std::cout << "down" << std::endl;
				m_player->setPosition(pos.x,ppart->getPosition().y-TEXTURE_SIZE-1);
				m_player->stopFall();
			}
			else if ( m_player->getDirection() == Direction::Left )
			{
				std::cout << "left" << std::endl;
				m_player->setPosition(ppart->getPosition().x + TEXTURE_SIZE+1, pos.y);
				m_player->setMoving(false);
			}
			else
			{
				std::cout << "right" << std::endl;
				m_player->setPosition(ppart->getPosition().x - TEXTURE_SIZE-1, pos.y);
				m_player->setMoving(false);
			}
		}
	}
}*/

void PhysicsManager::manageMarioFall()
{
	manageFall(m_player);
}

void PhysicsManager::manageBarrelsFall()
{
	for ( Barrel* barrel : *m_barrels )
		manageFall(barrel,true);
}

void PhysicsManager::playerDoesntMove()
{
	m_player->setMoving(false);
}

void PhysicsManager::playerTriesToGoLeft()
{
	if ( m_player->getDirection() != Direction::Up && m_player->getDirection() != Direction::Down )
	{
		m_player->setDirection(Direction::Left);
		m_player->setMoving(true);
	}
}

void PhysicsManager::playerTriesToGoRight()
{
	if ( m_player->getDirection() != Direction::Up && m_player->getDirection() != Direction::Down )
	{
		m_player->setDirection(Direction::Right);
		m_player->setMoving(true);
	}
}

void PhysicsManager::playerTriesToClimbLadder()
{
	if ( m_player->getLadder() != nullptr )
	{
		m_player->setDirection(Direction::Up);
		m_player->setMoving(true);
	}
	else
	{
		for ( Ladder* ladder : *m_ladders )
			if ( collide_1D_strict({ ladder->x(),ladder->xRight() }, { m_player->x(),m_player->xRight() }, 100) )
			{
				float yDiff = ladder->yBottom() - m_player->yBottom();
				if ( yDiff >= 0 && yDiff <= 2 )
				{
					m_player->setClimbingLadder(ladder, Direction::Up);
					return;
				}
			}
		m_player->setMoving(false);
	}
}
void PhysicsManager::playerTriesToClimbOffLadder()
{
	if ( m_player->getLadder() == nullptr )
	{
		for ( Ladder* ladder : *m_ladders )
			if ( collide_1D_strict({ladder->x(),ladder->xRight()}, { m_player->x(),m_player->xRight() }, 100) )
			{
				float yDiff = ladder->y() - m_player->yBottom();
				if ( yDiff >= 0 && yDiff < 2 )
				{
					m_player->setClimbingLadder(ladder, Direction::Down);
					return;
				}
			}
	}
	else
	{
		m_player->setDirection(Direction::Down);
		m_player->setMoving(true);
	}
}

void PhysicsManager::manageDescent(Character* obj)
{
	if ( !obj->isMoving() || obj->getGravityState() != Gravity::None )
		return;
	bool descendsLeft = obj->getDirection() == Direction::Left && obj->getPlatform()->getDirection() == Direction::Right;
	bool descendsRight = obj->getDirection() == Direction::Right && obj->getPlatform()->getDirection() == Direction::Left;
	if ( !descendsLeft && !descendsRight )
		return;
	// Sort de sa plateforme
	if ( descendsLeft && obj->xRight() < obj->getPlatform()->xLeft() || descendsRight && obj->x() >= obj->getPlatform()->xRight() )
	{
		obj->makeFall();
		return;
	}
	for ( SimpleObject* ppart : obj->getPlatform()->getParts() )
	{
		bool ownPPart = descendsRight && obj->x() >= ppart->x() && obj->xRight() <= ppart->xRight();
		ownPPart = ownPPart || descendsLeft && obj->xRight() <= ppart->xRight() && obj->x() >= ppart->x();
		if ( ownPPart && obj->yBottom() + 1 < ppart->y() )
			obj->setY(ppart->y() - obj->getSize().y );
	}
}

void PhysicsManager::manageFall(Character * obj, bool setBottomDirection)
{
	if ( !obj->isFalling() )
		return;
	// Parcourir à l'envers pour déposer Mario sur le bon bloc
	for ( int i = m_platforms->size()-1 ; i >= 0 ; i-- )
	{
		Platform* platform = m_platforms->at(i);
		for ( int j = platform->getParts().size()-1 ; j >= 0 ; j-- )
		{
			SimpleObject* block = platform->getParts()[j];
			if ( collide(obj, block) && obj->yBottom() <= block->yBottom() && block->y() - obj->height() > obj->getMaxJump() )
			{
				obj->resetMaxJump();
				obj->setPlatform(platform);
				obj->stopFall();
				obj->setY(block->y() - obj->height());
				if ( setBottomDirection )
				{
					Direction dir = (platform->getDirection() == Direction::Left ? Direction::Right : Direction::Left);
					obj->setDirection(dir);
				}
				return;
			}
		}
	}
}
