#include "pch.h"
#include "Application.h"
#include "PhysicsManager.h"

const sf::Time Application::TimePerFrame = sf::seconds(TIME_PER_FRAME);


Application::Application() :
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
	m_enemy(ENEMY_TEXTURE_FILE, Direction::Right),
	m_player(MARIO_TEXTURE_FILE)
{
	// TMP //
	Platform* firstPlatform = new Platform({ 0, WINDOW_HEIGHT - PLATFORM_SIZE_Y }, Direction::Right, Position::Bottom);
	m_platforms = { firstPlatform };
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X*2, (int)(WINDOW_HEIGHT*(6.f / 7.f)) },  Direction::Left));
	m_platforms.push_back(new Platform({ PLATFORM_SIZE_X,                  (int)(WINDOW_HEIGHT*(5.f / 7.f)) },  Direction::Right));
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X*2, (int)(WINDOW_HEIGHT*(4.f / 7.f)) },  Direction::Left));
	m_platforms.push_back(new Platform({ PLATFORM_SIZE_X,                  (int)(WINDOW_HEIGHT*(3.f / 7.f)) },  Direction::Right));
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X*2, (int)(WINDOW_HEIGHT*(2.f / 7.f)) },  Direction::Left, Position::Top));
	m_player.setPlatform(m_platforms[1]);
	//sf::Vector2f firstPPartPos = firstPlatform->getParts()[0]->getPosition();
	//m_player.setPosition(firstPPartPos.x, firstPPartPos.y - 32);
	sf::Vector2f firstPPartPos = m_platforms[1]->getParts()[0]->getPosition();
	m_player.setPosition(firstPPartPos.x, firstPPartPos.y - 32);
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
	for ( Platform* platform : m_platforms )
		platform->update();
	m_player.update();
	m_enemy.update();
	//PhysicsManager::manageMarioJump(m_player, m_platform);
	PhysicsManager::manageMarioClimb(m_player);
	PhysicsManager::manageMarioDescent(m_player);
	PhysicsManager::manageMarioFall(m_player, m_platforms);
}

void Application::render()
{
	m_window.clear();
	for ( Platform* platform : m_platforms )
		platform->draw(m_window);
	m_player.draw(m_window);
	m_enemy.draw(m_window);
	m_window.display();
}