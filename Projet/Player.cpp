#include "pch.h"
#include "Player.h"
#include "PhysicsManager.h"

Player::Player(std::string textureFile) :
	Character(textureFile, Direction::Right, MARIO_SIZE, PLAYER_SPEED, PLAYER_Y_DELTA, PLAYER_MAX_Y_SPEED),
	m_hammerSpriteSize(MARIO_HAMMER_SIZE),
	m_hammerState(HammerState::None)
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

	if (m_hasHammer) {
		if (clock.getElapsedTime().asSeconds() - elapsed.asSeconds() > HAMMER_DURATION) {
			elapsed = clock.getElapsedTime();
			setHammer(false);
		}
	}

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

void Player::setHammer(bool hammer)
{
	setConstantAnim(hammer);
	m_hasHammer = hammer;
	setAnim();
}

bool Player::hasHammer()
{
	return m_hasHammer;
}

void Player::setAnim()
{
	if (m_hasHammer) {
		if (m_direction == Direction::Left)
			m_anim = ANIM_HAMMER_LEFT;
		else
			m_anim = ANIM_HAMMER_RIGHT;
	}
	else {
		if (m_gravityState == Gravity::Up)
		{
			if (m_direction == Direction::Left)
				m_anim = ANIM_JUMP_LEFT;
			else m_anim = ANIM_JUMP_RIGHT;
		}
		else
		{
			if (m_direction == Direction::Left)
				m_anim = ANIM_LEFT;
			else if (m_direction == Direction::Right)
				m_anim = ANIM_RIGHT;
			else m_anim = ANIM_LADDER;
		}
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

void Player::setTextureAnim()
{
	sf::Vector2u currentSpriteSize = m_spriteSize;
	if ( m_hasHammer && (m_direction == Direction::Left || m_direction == Direction::Right) )
		currentSpriteSize = m_hammerSpriteSize;
	m_sprite.setTextureRect(sf::IntRect(m_anim.x*currentSpriteSize.x, m_anim.y*m_blockSizeY, currentSpriteSize.x, currentSpriteSize.y));
}
