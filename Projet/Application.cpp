#include "pch.h"
#include "Application.h"
#include "PhysicsManager.h"

const sf::Time Application::TimePerFrame = sf::seconds(TIME_PER_FRAME);


Application::Application():
m_window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),TITLE),
m_player(MARIO_TEXTURE_FILE),
m_enemy(ENEMY_TEXTURE_FILE, Direction::Right),
m_coin(COIN_TEXTURE_FILE, { 0,0 }, { 6,1 }, { 200,210 }),
m_platform({ 300,180 }, Direction::Right)
{

}


Application::~Application()
{
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while ( m_window.isOpen() )
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;
		while ( timeSinceLastUpdate > TimePerFrame )
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			processPlayerInputs();
			update();
			render();
		}
	}
}

void Application::processEvents()
{
	sf::Event event;
	while ( m_window.pollEvent(event) )
	{
		if ( event.type == sf::Event::Closed )
			m_window.close();
	}
}

void Application::processPlayerInputs()
{
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
	{
		m_player.setDirection(Direction::Left);
		m_player.setMoving(true);
	}
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
	{
		m_player.setDirection(Direction::Right);
		m_player.setMoving(true);
	}
	else
		m_player.setMoving(false);
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
		m_player.setJumping();
}

void Application::update()
{
	m_player.update();
	m_enemy.update();
	m_coin.update();
	PhysicsManager::manageMarioJump(m_player, m_platform);
}

void Application::render()
{
	m_window.clear();
	m_platform.draw(m_window);
	m_player.draw(m_window);
	m_enemy.draw(m_window);
	m_coin.draw(m_window);
	m_window.display();
}