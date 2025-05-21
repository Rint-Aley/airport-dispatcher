#ifndef RUNWAY_H
#define RUNWAY_H

#include "Road.h"

class Runway : public Road {
public:
	Runway(const sf::Vector2f& a, const sf::Vector2f& b, float width, std::vector<Road*> adjacent_roads);

	float get_length();

	void draw(sf::RenderWindow& window) const override;
};
#endif
