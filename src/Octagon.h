#ifndef OCTAGON_H
#define OCTAGON_H

#include <vector>
#include <SFML/System/Vector3.hpp>

struct OctagonPoint {
	sf::Vector3f point;
	OctagonPoint* next;
	OctagonPoint(sf::Vector3f point, OctagonPoint* next) : point(point), next(next) {}
};

std::vector<OctagonPoint> build_octagon(sf::Vector3f center, float r);

#endif