#include "Game.h"
#include <SFML/Window/VideoMode.hpp>
#include <list>

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
	a.push_back({ 100, 100, 0 });
	//a.push_back({ 100, 1000, 0 });
	//a.push_back({ 1000, 500, 0 });
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
		plane.follow_path_on_the_ground(dt);
		
		// Event handling
		
		// Drawing
		window.clear();

		plane.draw(window);
		
		window.display();
	}
}
