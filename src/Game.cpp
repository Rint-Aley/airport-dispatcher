#include "Game.h"
#include <SFML/Window/VideoMode.hpp>
#include <list>
#include <iostream>

Game::Game() : state(GameState::InLobby), current_level(nullptr)
{
	// Should get the settings from the file
	players = {};
	current_player = nullptr;
	resolution = sf::Vector2u(1920, 1080);
	window = sf::RenderWindow(sf::VideoMode(resolution), "Airport", sf::Style::Default, sf::State::Windowed);
}

void Game::launch_game()
{
	sf::Clock clock;
	sf::Time dt;

	// For testing
	Plane plane;
	std::list<sf::Vector3f> a;
	a.push_back({ 100, 100, 10 });
	a.push_back({ 100, 1000, 100 });
	a.push_back({ 1000, 500, 12 });
	plane.set_path(a);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		dt = clock.restart();
		// Physic sim
		plane.follow_path(dt);
		std::cout << plane.get_position().z << '\n';

		// Event handling
		
		// Drawing
		window.clear();

		plane.draw(window);
		
		window.display();
	}
}
