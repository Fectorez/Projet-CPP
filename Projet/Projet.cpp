#include "pch.h"
#include <iostream>
#include "Application.h"

int main()
{
	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::Texture texture;
	if ( !texture.loadFromFile("goomba_sprite.png") )
		exit(1);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sf::Vector2i anim = { 0,0 };
	sprite.setTextureRect(sf::IntRect(anim.x, anim.y, 32, 22));
	sf::Clock clock;

	while (window.isOpen())
	{
		if ( clock.getElapsedTime().asMilliseconds() > 100 )
		{
			sf::Event event;
			while ( window.pollEvent(event) )
			{
				if ( event.type == sf::Event::Closed )
					window.close();
			}

			anim.x++;
			if ( anim.x == 3 )
				anim.x = 0;
			sprite.setTextureRect(sf::IntRect(anim.x * 22, anim.y, 32, 22));

			if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
				sprite.move(1, 0);

			window.clear();
			window.draw(shape);
			window.draw(sprite);
			window.display();
			clock.restart();
		}
	}
	/*
	Game game;
	game.run();*/

	Application app;
	app.run();

	return 0;
}