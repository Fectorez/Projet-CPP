#include "pch.h"
#include "Player.h"
#include "PhysicsManager.h"

Player::Player(std::string textureFile) :
	Character(textureFile, Direction::Right, MARIO_SIZE, PLAYER_SPEED, PLAYER_Y_DELTA, PLAYER_MAX_Y_SPEED)
{
	resetMaxJump();
	setAnim();
}


Player::~Player()
{}


void Player::update()
{
	if ( m_moving && m_direction == Direction::Up )
		climbUpLadder();
	else if ( m_moving && m_direction == Direction::Down )
		climbOffLadder();

	Character::update();
}

void Player::updateSprite()
{
	Character::updateSprite();
}

bool Player::isGoingUp() const
{
	return m_gravityState == Gravity::Up;
}

Ladder * Player::getLadder() const
{
	return m_ladder;
}

void Player::setLadder(Ladder * ladder)
{
	m_ladder = ladder;
}

void Player::setClimbingLadder(Ladder* ladder, Direction direction)
{
	m_ladder = ladder;
	m_platform = nullptr;
	setDirection(direction);
}

void Player::setAnim()
{
	if ( m_gravityState == Gravity::Up )
	{
		if ( m_direction == Direction::Left )
			m_anim = ANIM_JUMP_LEFT;
		else m_anim = ANIM_JUMP_RIGHT;
	}
	else
	{
		if ( m_direction == Direction::Left )
			m_anim = ANIM_LEFT;
		else if ( m_direction == Direction::Right )
			m_anim = ANIM_RIGHT;
		else m_anim = ANIM_LADDER;
	}
}

void Player::climbUpLadder()
{
	moveY(-m_speed.x);
	if ( !PhysicsManager::collide(this, m_ladder) )
		stopClimbLadder();
}

void Player::climbOffLadder()
{
	moveY(m_speed.x);
	if ( yBottom() >= m_ladder->yBottom() )
		stopClimbLadder();
}

void Player::stopClimbLadder()
{
	m_ladder = nullptr;
	setDirection(Direction::Right);
	setMoving(false);
	makeFall();
}
