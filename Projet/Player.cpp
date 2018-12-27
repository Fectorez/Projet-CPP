#include "pch.h"
#include "Player.h"

const float Player::MAX_JUMP_SPEED = 10.f;

Player::Player(std::string textureFile) :
	Character(textureFile, Direction::Right, 1, false, { 0,2 }, { 3,3 }),
	m_platform(nullptr)
{}


Player::~Player()
{}


void Player::update()
{
	if ( m_gravityState == Gravity::Up )
	{
		m_sprite.move(0, -m_jumpSpeed);
		m_jumpSpeed -= 0.5;
		if ( m_jumpSpeed <= 0 )
		{
			m_gravityState = Gravity::Down;
			m_jumpSpeed = 0;
		}
	}
	else if ( m_gravityState == Gravity::Down )
	{
		m_sprite.move(0, m_jumpSpeed);
		m_jumpSpeed += 0.5;
		/*if ( m_sprite.getPosition().y >= 200 )
		{
			m_jumpState = JumpState::None;
			m_jumpSpeed = MAX_JUMP_SPEED;
		}*/
	}
	Character::update();
}

void Player::setJumping()
{
	if ( m_gravityState == Gravity::None )
		m_gravityState = Gravity::Up;
}

bool Player::isGoingUp() const
{
	return m_gravityState == Gravity::Up;
}

bool Player::isGoingDown() const
{
	return m_gravityState == Gravity::Down;
}

void Player::makeFall()
{
	if ( m_gravityState == Gravity::None )
	{
		m_gravityState = Gravity::Down;
		m_platform = nullptr;
		m_jumpSpeed = 0;
	}
}

void Player::stopFall()
{
	m_gravityState = Gravity::None;
	m_jumpSpeed = MAX_JUMP_SPEED;
}

Platform * Player::getPlatform() const
{
	return m_platform;
}

void Player::setPlatform(Platform * platform)
{
	m_platform = platform;
}

Gravity Player::getGravityState() const
{
	return m_gravityState;
}
