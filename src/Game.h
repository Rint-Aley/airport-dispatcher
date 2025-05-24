#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "LevelInProgress.h"
#include "Player.h"

class Game {
private:
	enum GameState {
		Loading,
		InLobby,
		InGame,
	} state;
	LevelInProgress* current_level;
	std::vector<Player> players;
	Player* current_player;

	sf::Vector2u resolution;
	sf::RenderWindow window;

	// Some settings:
	float selection_radius;
public:
	Game();
	void launch_level(const std::string& level_name);
	void save_level();
};

#endif