#include "Polygon.h"

Polygon::Polygon(const sf::Color& color)
	: Shape(color)
{ }

void Polygon::addPoint(const sf::Vector2f& relPoint)
{
	if (!isLegalRelPoint(relPoint))
		throw std::invalid_argument("Relative point {x=" + std::to_string(relPoint.x) + ", y=" + std::to_string(relPoint.y) + "} must be in [0, 1]");
	m_relPoints.push_back(relPoint);
}

const sf::Vector2f& Polygon::getPoint(int index) const
{
	if (index < 0 || index >= getNumOfPoints())
		throw std::out_of_range("Canoot find point at " + std::to_string(index));
	return m_relPoints[index];
}
