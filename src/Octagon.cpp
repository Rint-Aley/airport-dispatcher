#define _USE_MATH_DEFINES
#include <math.h>
#include "Octagon.h"

std::vector<OctagonPoint> build_octagon(sf::Vector3f center, float r)
{
	std::vector<OctagonPoint> points;
	points.push_back(OctagonPoint({ center.x + r * (float)cos(0), center.y + r * (float)sin(0), 0 }, nullptr));
	for (size_t i = 1; i < 8; ++i)
	{
		points.push_back(OctagonPoint({ center.x + r * (float)cos(M_PI * i / 4), center.y + r * (float)sin(M_PI * i / 4), 0 }, &points[i - 1]));
	}
	points[0].next = &points[7];
	return points;
}