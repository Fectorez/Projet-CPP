#pragma once
#include "SimpleObject.h"
#include "Player.h"
#include "Platform.h"
#include "Ladder.h"

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
		std::vector<Platform*> m_platforms;
		std::vector<Ladder*> m_ladders;
};

