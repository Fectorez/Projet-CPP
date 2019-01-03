#pragma once

#include "Player.h"
#include "Platform.h"
#include "Ladder.h"
#include "DonkeyKong.h"
#include "Barrel.h"
#include "PhysicsManager.h"

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

		void createNewBarrel();

	private:
		static const sf::Time TimePerFrame;
		sf::RenderWindow m_window;
		Player m_player;
		std::vector<Platform*> m_platforms;
		std::vector<Ladder*> m_ladders;
		SimpleObject m_barrelsStack;
		DonkeyKong m_donkeyKong;
		std::vector<Barrel*> m_barrels;
		PhysicsManager m_manager;
};

