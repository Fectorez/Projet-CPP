#include "pch.h"
#include "Application.h"
#include "PhysicsManager.h"

const sf::Time Application::TimePerFrame = sf::seconds(TIME_PER_FRAME);


Application::Application() :
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE),
	m_player(MARIO_TEXTURE_FILE),
	m_barrelsStack(BARRELS_STACK_TEXTURE_FILE),
	m_donkeyKong(),
	m_peach(PEACH_TEXTURE_FILE,PEACH_RECT),
	m_burningBarrel()
{
	srand(time(NULL));

	// TMP //
	Platform* firstPlatform = new Platform({ 0, WINDOW_HEIGHT - PLATFORM_SIZE_Y }, Direction::Right, Position::Bottom);
	m_platforms = { firstPlatform };
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X*2, (int)(WINDOW_HEIGHT*(6.f / 7.f)) },  Direction::Left));
	m_platforms.push_back(new Platform({ PLATFORM_SIZE_X,                  (int)(WINDOW_HEIGHT*(5.f / 7.f)) },  Direction::Right));
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X*2, (int)(WINDOW_HEIGHT*(4.f / 7.f)) },  Direction::Left));
	m_platforms.push_back(new Platform({ PLATFORM_SIZE_X,                  (int)(WINDOW_HEIGHT*(3.f / 7.f)) },  Direction::Right));
	m_platforms.push_back(new Platform({ WINDOW_WIDTH - PLATFORM_SIZE_X * 2, (int)(WINDOW_HEIGHT*(2.f / 7.f)) }, Direction::Left, Position::Top));
	m_platforms.push_back(new Platform({ m_platforms[5]->getParts()[7]->x()+PLATFORM_SIZE_X/2, (int)(WINDOW_HEIGHT*(1.f / 7.f)) }, Direction::Right, Position::Peach));
	m_platforms.push_back(new Platform({ m_platforms[6]->xLeft()-48, -PLATFORM_SIZE_Y }, Direction::Right, Position::Peach));
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
	m_barrelsStack.setPosition(0, m_platforms[5]->yTop()-64);

	m_donkeyKong.setPosition(40, m_platforms[5]->yTop() - 64);
	m_peach.setPosition(m_ladders[9]->xRight(), m_platforms[6]->yTop()-32);
	m_burningBarrel.setPosition(m_platforms[0]->getParts()[1]->x(), m_platforms[0]->getParts()[1]->y() - 64);

	m_manager.addAll(&m_player,&m_ladders,&m_platforms,&m_barrels,&m_burningBarrel);
}


Application::~Application()
{
	for ( Ladder* ladder : m_ladders )
		delete ladder;
	for ( Platform* platform : m_platforms )
		delete platform;
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
		m_manager.playerTriesToGoLeft();
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
		m_manager.playerTriesToGoRight();
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
		m_manager.playerTriesToClimbLadder();
	else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
		m_manager.playerTriesToClimbOffLadder();
	else
		m_manager.playerDoesntMove();
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
		m_player.setJumping();
}

void Application::update()
{
	for ( Platform* platform : m_platforms )
		platform->update();
	for ( int i = 0 ; i < m_barrels.size() ; i++ )
	{
		m_barrels[i]->update();
		if ( PhysicsManager::collide(&m_player, m_barrels[i]) )
		{
			//TODO
			std::cout << "PERDU" << std::endl;
		}
		else if ( m_manager.blueBarreltouchsBurningBarrel(m_barrels[i]) )
		{
			m_burningBarrel.setInFire();
			delete m_barrels[i];
			m_barrels.erase(m_barrels.begin() + i);
			i--;
		}
		else if ( m_barrels[i]->isLeft() )
		{
			delete m_barrels[i];
			m_barrels.erase(m_barrels.begin() + i);
			i--;
		}
	}
	m_player.update();
	m_donkeyKong.update();
	m_peach.update();
	m_burningBarrel.update();
	if ( m_donkeyKong.placesBlueBarrel() )
		createNewBarrel(true);
	if ( m_donkeyKong.placesBarrel() )
		createNewBarrel();
	if ( win() )
		//TODO
		std::cout << "GAGNE!" << std::endl;
	//PhysicsManager::manageMarioJump(m_player, m_platform);
	m_manager.manageMarioClimb();
	m_manager.manageMarioDescent();
	m_manager.manageBarrelsDescent();
	m_manager.manageMarioFall();
	m_manager.manageBarrelsFall();
}

void Application::render()
{
	m_window.clear();
	m_burningBarrel.draw(m_window);
	for ( Ladder* ladder : m_ladders )
		ladder->draw(m_window);
	for ( Platform* platform : m_platforms )
		platform->draw(m_window);
	for ( Barrel* barrel : m_barrels )
		barrel->draw(m_window);
	m_barrelsStack.draw(m_window);
	m_peach.draw(m_window);
	m_donkeyKong.draw(m_window);
	m_player.draw(m_window);
	m_window.display();
}

void Application::createNewBarrel(bool blue)
{
	Barrel* barrel;
	if ( blue )
		barrel = new BlueBarrel(m_donkeyKong.getTimePerAction());
	else
		barrel = new Barrel(m_donkeyKong.getTimePerAction());
	barrel->setPosition(m_donkeyKong.xRight(), m_donkeyKong.yBottom() - BARREL_SIZE.y);
	barrel->setPlatform(m_platforms[5]);
	barrel->setExitPlatform(m_platforms[0]);
	m_barrels.push_back(barrel);
}

bool Application::win() const
{
	return m_player.getPlatform() == m_platforms[6];
}
