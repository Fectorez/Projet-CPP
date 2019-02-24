#pragma once

#include "Player.h"
#include "Platform.h"
#include "Ladder.h"
#include "DonkeyKong.h"
#include "Barrel.h"
#include "BlueBarrel.h"
#include "BurningBarrel.h"
#include "PhysicsManager.h"
#include "FireMonster.h"
#include "Scene.h"

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

	private:
		static const sf::Time TimePerFrame;
		sf::RenderWindow m_window;
		Scene* m_scene;
};

