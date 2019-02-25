#include "pch.h"
#include "Application.h"
#include "PhysicsManager.h"

const sf::Time Application::TimePerFrame = sf::seconds(TIME_PER_FRAME);


Application::Application() :
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
	m_scene(new Scene())
{
	srand(time(NULL));
}


Application::~Application()
{}

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

void Application::update()
{
	m_scene->update();
	if (m_scene->finished()) {
		m_scene->setPause(true);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
			m_scene = new Scene();
		}
	}
}

void Application::render()
{
	m_window.clear();
	m_scene->draw(m_window);
	m_window.display();
}


