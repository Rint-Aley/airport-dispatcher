#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Road {
private:
	sf::Vector2f coordinates[2];
	float width;
	std::vector<Road*> adjacent_roads;
public:
	Road(const sf::Vector2f& a, const sf::Vector2f& b,
		float width, const std::vector<Road*>& adjacent_roads);
	virtual ~Road() {}

	const std::vector<Road*> get_adjacent_roads() const { return adjacent_roads; }
	float get_width() const;
	std::pair<sf::Vector2f, sf::Vector2f> get_coordinates() const;
	sf::Vector2f get_direciton() const;

	void add_adjacent_road(Road* adj_road);
	void delete_adjacent_road(Road* adj_road);

	bool is_on_the_road(sf::Vector2f position);

	virtual void draw(sf::RenderWindow& window) const;
};
#endif
