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

class Scene
{
	public:
		Scene();
		~Scene();
		void update();
		void draw(sf::RenderWindow& window);
		bool finished() const;
		void setPause(bool);
		void drawGameOver(sf::RenderWindow& window);
		void loadHammerMusic();
		void loadBGMMusic();

	private:
		void processPlayerInputs();
		void createNewBarrel(bool blue = false);
		void createNewFireMonster();
		bool win() const;

	private:
		Player m_player;
		std::vector<Platform*> m_platforms;
		std::vector<Ladder*> m_ladders;
		std::vector<FireMonster*> m_fireMonsters;
		SimpleObject m_barrelsStack;
		SimpleObject m_winText;
		SimpleObject m_loseText;
		SimpleObject m_hammer;
		DonkeyKong m_donkeyKong;
		std::vector<Barrel*> m_barrels;
		SimpleObject m_peach;
		BurningBarrel m_burningBarrel;
		PhysicsManager m_manager;
		sf::Music m_bgm_music;
		sf::Music m_hammer_music;
		bool m_lost = false;
		bool m_won = false;
		bool m_paused = false;
};

