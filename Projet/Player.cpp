#include "pch.h"
#include "Player.h"

const float Player::MAX_JUMP_SPEED = 10.f;

Player::Player(std::string textureFile) :
	Character(textureFile, Direction::Right, 1, false, { 0,2 }, { 3,3 })
{
	m_sprite.setPosition(30, 30);
}


Player::~Player()
{}


void Player::update()
{
	if ( m_jumpState == JumpState::Up )
	{
		m_sprite.move(0, -m_jumpSpeed);
		m_jumpSpeed -= 0.5;
		if ( m_jumpSpeed <= 0 )
		{
			m_jumpState = JumpState::Down;
			m_jumpSpeed = 0;
		}
	}
	else if ( m_jumpState == JumpState::Down )
	{
		m_sprite.move(0, m_jumpSpeed);
		m_jumpSpeed += 0.5;
		if ( m_sprite.getPosition().y >= 200 )
		{
			m_jumpState = JumpState::None;
			m_jumpSpeed = MAX_JUMP_SPEED;
		}
	}
	Character::update();
}

void Player::setJumping()
{
	if ( m_jumpState == JumpState::None )
		m_jumpState = JumpState::Up;
}

bool Player::isGoingUp() const
{
	return m_jumpState == JumpState::Up;
}

bool Player::isGoingDown() const
{
	return m_jumpState == JumpState::Down;
}

void Player::makeFall()
{
	m_jumpState = JumpState::Down;
	m_jumpSpeed = 0;
}

void Player::stopFall()
{
	m_jumpState = JumpState::None;
	m_jumpSpeed = MAX_JUMP_SPEED;
}
