#include "Game.h"
#include <SFML/Window/VideoMode.hpp>
#include <list>
#include <iostream>
#include "Camera.h"
#include "LevelProducer.h"
#include "RadioButtonGroup.h"

Game::Game() : state(GameState::InLobby), current_level(nullptr), selection_radius(20)
{
	players = {};
	current_player = nullptr;
	resolution = sf::Vector2u(1920, 1080);
	window = sf::RenderWindow(sf::VideoMode(resolution), "Airport", sf::Style::Default, sf::State::Windowed);
}

void Game::launch_game()
{
	sf::Font font("../assets/fonts/JetBrainsMono-VariableFont_wght.ttf");
	sf::Clock clock;
	sf::Time dt;
	Camera camera(window);
	camera.set_center(sf::Vector2f(resolution / 2u));
	RadioButtonGroup button_group;

	sf::Text penalty_text(font, "Penalty: 0.00", 24);
	sf::Text time_text(font, "Time: 0.00", 24);
	sf::Text plane_info_text(font, "", 24);
	penalty_text.setFillColor(sf::Color::White);
	time_text.setFillColor(sf::Color::White);
	plane_info_text.setFillColor(sf::Color::White);

	LevelInProgress a(std::move(LevelProducer::Level1()));
	current_level = &a;

	auto& landing_list = current_level->get_landing_list();
	
	for (auto& info : landing_list)
	{
		button_group.add_button(info->get_name(), sf::Vector2f(100, 30));
	}

	button_group.update_positions(window.getSize());

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			button_group.handle_event(event.value(), window);
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
				if (keycode == sf::Keyboard::Scancode::E)
					current_level->toggle_runway_selection_mode();
			}
			if (const auto* wheel_scrolled = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				float factor = (wheel_scrolled->delta > 0 ? 0.9f : 1.1f);
				sf::Vector2i mouse_pos(wheel_scrolled->position.x, wheel_scrolled->position.y);
				camera.zoom(factor, mouse_pos);
			}
			if (const auto* mouse_click = event->getIf<sf::Event::MouseButtonPressed>()) 
			{
				if (mouse_click->button == sf::Mouse::Button::Left)
				{
					current_level->select_closest_plain_in_radius(window.mapPixelToCoords(mouse_click->position, camera.get_view()), selection_radius);
				}
				else if (mouse_click->button == sf::Mouse::Button::Right)
				{
					if (button_group.get_selected_index() != -1)
					{
						if (current_level->assign_runway(window.mapPixelToCoords(mouse_click->position, camera.get_view()), selection_radius,
							landing_list[button_group.get_selected_index()]))
						{
							auto del = button_group.get_selected_index();
							button_group.reset_selection();
							auto& ll = const_cast<std::vector<Plane*>&>(current_level->get_landing_list());
							ll.erase(ll.begin() + del);
							button_group.delete_button(del);
							button_group.update_positions(window.getSize());
						}
					}
					else 
						current_level->add_move_point_to_selected_plane(window.mapPixelToCoords(mouse_click->position, camera.get_view()), selection_radius);
				}
				else if (mouse_click->button == sf::Mouse::Button::Middle)
				{
					current_level->clear_path_for_selected_plane();
				}
			}
		}

		penalty_text.setString(std::format("Penalty: {:.2f}", current_level->get_penalty()));
		sf::FloatRect textRect = penalty_text.getLocalBounds();
		penalty_text.setOrigin(textRect.position + textRect.size);
		penalty_text.setPosition(sf::Vector2f(window.getSize()) - sf::Vector2f(10, 10));

		time_text.setString(std::format("Time: {:.2f}", current_level->get_time()));
		textRect = time_text.getLocalBounds();
		time_text.setOrigin(textRect.position + textRect.size);
		time_text.setPosition(sf::Vector2f(window.getSize()) - sf::Vector2f(10, 50));

		if (current_level->get_selected_plane() != nullptr)
		{
			auto info = current_level->get_info_on_plane(current_level->get_selected_plane());
			if (info.has_value())
			{
				auto i = info.value();
				plane_info_text.setString(std::format("Goal: {}, Time: {:.2f}", (i.goal == i.TakeOff ? "take off" : "land"), i.time));
			}
		}
		else if (button_group.get_selected_index() != -1)
		{
			auto info = current_level->get_info_on_plane(landing_list[button_group.get_selected_index()]);
			if (info.has_value())
			{
				auto i = info.value();
				plane_info_text.setString(std::format("Goal: land; Cycles remain: {:.2f}", i.cycles));
			}
		}
		else {
			plane_info_text.setString("");
		}
		textRect = plane_info_text.getLocalBounds();
		plane_info_text.setOrigin(textRect.position);
		plane_info_text.setPosition(sf::Vector2f(window.getSize()) - sf::Vector2f(window.getSize().x - 10, 30));


		dt = clock.restart();

		current_level->calculate_physics(dt);
		current_level->check_collisions();
		current_level->handle_events();
		
		window.clear();

		window.setView(camera.get_view());
		current_level->draw(window);

		window.setView(window.getDefaultView());
		button_group.draw(window);
		window.draw(penalty_text);
		window.draw(time_text);
		window.draw(plane_info_text);

		window.display();
	}
}
