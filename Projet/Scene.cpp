#include "pch.h"
#include "Scene.h"


Scene::Scene() :
	m_player(MARIO_TEXTURE_FILE),
	m_barrelsStack(BARRELS_STACK_TEXTURE_FILE),
	m_donkeyKong(),
	m_peach(PEACH_TEXTURE_FILE, PEACH_RECT),
	m_burningBarrel(),
	m_winText(WIN_TEXT_TEXTURE_FILE),
	m_loseText(LOSE_TEXT_TEXTURE_FILE),
	m_hammer(HAMMER_TEXTURE_FILE)
{
	Platform* firstPlatform = new Platform({ 0, WINDOW_HEIGHT - PLATFORM_SIZE_Y }, Direction::Right, Position::Bottom);
	m_platforms = { firstPlatform };
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X * 2, (int)(WINDOW_HEIGHT*(6.f / 7.f)) }, Direction::Left));
	m_platforms.push_back(new Platform({ PLATFORM_SIZE_X,                  (int)(WINDOW_HEIGHT*(5.f / 7.f)) }, Direction::Right));
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X * 2, (int)(WINDOW_HEIGHT*(4.f / 7.f)) }, Direction::Left));
	m_platforms.push_back(new Platform({ PLATFORM_SIZE_X,                  (int)(WINDOW_HEIGHT*(3.f / 7.f)) }, Direction::Right));
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X * 2, (int)(WINDOW_HEIGHT*(2.f / 7.f)) }, Direction::Left, Position::Top));
	m_platforms.push_back(new Platform({ m_platforms[5]->getParts()[7]->x() + PLATFORM_SIZE_X / 2, (int)(WINDOW_HEIGHT*(1.f / 7.f)) }, Direction::Right, Position::Peach));
	m_platforms.push_back(new Platform({ m_platforms[6]->xLeft() - 48, -PLATFORM_SIZE_Y }, Direction::Right, Position::Peach));

	m_player.setPlatform(m_platforms[0]);
	sf::Vector2f firstPPartPos = firstPlatform->getParts()[0]->getPosition();
	m_player.setPosition(firstPPartPos.x, firstPPartPos.y - 32);

	m_ladders = std::vector<Ladder*>();
	m_ladders.push_back(new Ladder());
	m_ladders[0]->build(m_platforms[1]->getParts()[1], m_platforms[0]->getParts()[11], Direction::Right);
	m_ladders.push_back(new Ladder());
	m_ladders[1]->build(m_platforms[2]->getParts()[1], m_platforms[1]->getParts()[10], Direction::Left);
	m_ladders.push_back(new Ladder());
	m_ladders[2]->build(m_platforms[2]->getParts()[5], m_platforms[1]->getParts()[6], Direction::Left);
	m_ladders.push_back(new Ladder());
	m_ladders[3]->build(m_platforms[3]->getParts()[1], m_platforms[2]->getParts()[10], Direction::Right);
	m_ladders.push_back(new Ladder());
	m_ladders[4]->build(m_platforms[3]->getParts()[5], m_platforms[2]->getParts()[6], Direction::Left);
	m_ladders.push_back(new Ladder());
	m_ladders[5]->build(m_platforms[4]->getParts()[1], m_platforms[3]->getParts()[10], Direction::Left);
	m_ladders.push_back(new Ladder());
	m_ladders[6]->build(m_platforms[4]->getParts()[3], m_platforms[3]->getParts()[8], Direction::Right);
	m_ladders.push_back(new Ladder());
	m_ladders[7]->build(m_platforms[5]->getParts()[1], m_platforms[4]->getParts()[10], Direction::Right);
	m_ladders.push_back(new Ladder());
	m_ladders[8]->build(m_platforms[6]->getParts()[2], m_platforms[5]->getParts()[4], Direction::Right);
	m_ladders.push_back(new Ladder());
	m_ladders[9]->build(m_platforms[7]->getParts()[1], m_platforms[5]->getParts()[4], Direction::Left);
	m_ladders.push_back(new Ladder());
	m_ladders[10]->build(m_platforms[7]->getParts()[0], m_platforms[5]->getParts()[3], Direction::Left);

	m_fireMonsters = std::vector<FireMonster*>();

	m_barrelsStack.setPosition(0, m_platforms[5]->yTop() - 64);

	m_donkeyKong.setPosition(40, m_platforms[5]->yTop() - 64);
	m_peach.setPosition(m_ladders[9]->xRight(), m_platforms[6]->yTop() - 32);
	m_burningBarrel.setPosition(m_platforms[0]->getParts()[1]->x(), m_platforms[0]->getParts()[1]->y() - 64);

	m_manager.addAll(&m_player, &m_ladders, &m_platforms, &m_barrels, &m_burningBarrel, &m_fireMonsters);

	m_hammer.setPosition(50, m_platforms[2]->yTop()+100);

	m_winText.setPosition(100, 100);
	m_loseText.setPosition(100, 100);
}


Scene::~Scene()
{
	for ( Ladder* ladder : m_ladders )
		delete ladder;
	for ( Platform* platform : m_platforms )
		delete platform;
	for ( FireMonster* fireMonster : m_fireMonsters )
		delete fireMonster;
}

void Scene::update()
{
	if (!m_paused) {
		for (Platform* platform : m_platforms)
			platform->update();
		//int barrels_size = m_barrels.size();
		for (int i = 0; i < m_barrels.size(); i++)
		{
			m_barrels[i]->update();
			if (PhysicsManager::collide(&m_player, m_barrels[i]))
				if (!m_player.hasHammer())
					m_lost = true;
				else {
					/*Destruction du barril
					m_barrels[i]->~Barrel();
					barrels_size = m_barrels.size();*/
				}
					

			else if (m_manager.endOfBarrel(m_barrels[i]))
			{
				if (m_barrels[i]->getType() == BLUE)
				{
					m_burningBarrel.setInFire();
					createNewFireMonster();
				}
				delete m_barrels[i];
				m_barrels.erase(m_barrels.begin() + i);
				i--;
			}
			else if (m_barrels[i]->isLeft())
			{
				delete m_barrels[i];
				m_barrels.erase(m_barrels.begin() + i);
				i--;
			}
		}
		for (FireMonster* fireMonster : m_fireMonsters)
		{
			fireMonster->update();
			if (PhysicsManager::collide(&m_player, fireMonster))
				m_lost = true;
		}

		if (PhysicsManager::collide(&m_player, &m_hammer)) {
			m_player.setHammer(true);
			m_hammer.hide();
		}
			

		m_player.update();
		m_donkeyKong.update();
		m_peach.update();
		m_burningBarrel.update();
		if (m_donkeyKong.placesBlueBarrel())
			createNewBarrel(true);
		if (m_donkeyKong.placesBarrel())
			createNewBarrel();
		if (win())
			m_won = true;
		//PhysicsManager::manageMarioJump(m_player, m_platform);
		m_manager.manageMarioClimb();
		m_manager.manageMarioDescent();
		m_manager.manageBarrelsDescent();
		m_manager.manageMarioFall();
		m_manager.manageBarrelsFall();
		m_manager.manageFireMonstersFall();
	}
	processPlayerInputs();
}

void Scene::draw(sf::RenderWindow& window)
{
	for ( Ladder* ladder : m_ladders )
		ladder->draw(window);
	for ( Barrel* barrel : m_barrels )
		barrel->draw(window);
	m_burningBarrel.draw(window);
	for ( Platform* platform : m_platforms )
		platform->draw(window);
	for ( FireMonster* fireMonster : m_fireMonsters )
		fireMonster->draw(window);
	m_barrelsStack.draw(window);
	m_peach.draw(window);
	m_donkeyKong.draw(window);
	m_hammer.draw(window);
	m_player.draw(window);

	drawGameOver(window);
}

bool Scene::finished() const
{
	return m_lost || m_won;
}


void Scene::processPlayerInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_manager.playerTriesToGoLeft();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_manager.playerTriesToGoRight();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_manager.playerTriesToClimbLadder();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_manager.playerTriesToClimbOffLadder();
	else
		m_manager.playerDoesntMove();
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
		m_player.setJumping();
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		m_lost = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_won = true;*/
}

void Scene::createNewBarrel(bool blue)
{
	Barrel* barrel;
	if ( blue )
		barrel = new BlueBarrel(m_donkeyKong.getTimePerAction());
	else
		barrel = new Barrel(m_donkeyKong.getTimePerAction());
	barrel->setPosition(m_donkeyKong.xRight(), m_donkeyKong.yBottom() - BARREL_SIZE.y);
	barrel->setPlatform(m_platforms[5]);
	m_barrels.push_back(barrel);
}

void Scene::createNewFireMonster()
{
	FireMonster* fireMonster = new FireMonster();
	fireMonster->setPosition(m_burningBarrel.x(), m_burningBarrel.yBottom() - 50);
	fireMonster->makeFall();
	m_fireMonsters.push_back(fireMonster);
}

bool Scene::win() const
{
	return m_player.getPlatform() == m_platforms[6];
}

void Scene::setPause(bool paused)
{
	m_paused = paused;
}

void Scene::drawGameOver(sf::RenderWindow & window)
{
	if (finished())
		if (m_lost)
			m_loseText.draw(window);
		else
			m_winText.draw(window);
}
