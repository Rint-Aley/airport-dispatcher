#include "Game.h"
#include <SFML/Window/VideoMode.hpp>
#include <list>
#include <iostream>
#include "Camera.h"
#include "LevelProducer.h"

Game::Game() : state(GameState::InLobby), current_level(nullptr), selection_radius(20)
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
	Camera camera(window);
	camera.set_center(sf::Vector2f(resolution / 2u));

	// For testing
	LevelInProgress a(std::move(LevelProducer::Level1()));
	current_level = &a;
	/*Plane plane;
	std::list<sf::Vector3f> a;
	a.push_back({ 100, 100, 10 });
	a.push_back({ 100, 1000, 100 });
	a.push_back({ 1000, 500, 12 });
	plane.set_path(a);*/

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				const sf::Keyboard::Scancode keycode = keyPressed->scancode;
				if (keycode == sf::Keyboard::Scancode::W)
					camera.move(sf::Vector2f(0, -4));
				if (keycode == sf::Keyboard::Scancode::S)
					camera.move(sf::Vector2f(0, 4));
				if (keycode == sf::Keyboard::Scancode::A)
					camera.move(sf::Vector2f(-4, 0));
				if (keycode == sf::Keyboard::Scancode::D)
					camera.move(sf::Vector2f(4, 0));
			}
			if (const auto* wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				if (wheel_scrolled->delta > 0)
					camera.zoom(0.9f);
				else if (wheel_scrolled->delta < 0)
					camera.zoom(1.1f);
			}
			if (const auto* mouse_click = event->getIf<sf::Event::MouseButtonPressed>()) 
			{
				if (mouse_click->button == sf::Mouse::Button::Left)
				{
					current_level->select_closest_plain_in_radius(screen_to_world(mouse_click->position, window), selection_radius);
				}
				else if (mouse_click->button == sf::Mouse::Button::Right)
				{
					current_level->add_move_point_to_selected_plane(screen_to_world(mouse_click->position, window), selection_radius);
				}
				else if (mouse_click->button == sf::Mouse::Button::Middle)
				{
					current_level->clear_path_for_selected_plane();
				}
			}
		}

		dt = clock.restart();
		// Physic sim
		current_level->calculate_physics(dt);

		// Event handling
		
		// Drawing
		window.clear();

		current_level->draw(window);
		
		window.display();
	}
}
