#pragma once
#include "SimpleObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"

class Application
{
	public:
		Application();
		~Application();
		void run();

	private:
		void update();
		void render();
		void processEvents();
		void processPlayerInputs();

	private:
		static const sf::Time TimePerFrame;
		sf::RenderWindow m_window;
		Player m_player;
		Enemy m_enemy;
		std::vector<Platform*> m_platforms;
};

