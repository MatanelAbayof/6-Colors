#include "PolygonShape.h"

PolygonShape::PolygonShape(const sf::Color& color)
	: Shape(color)
{ }

void PolygonShape::addPoint(const sf::Vector2f& relPoint)
{
	if (!isLegalRelPoint(relPoint))
		throw std::invalid_argument("Relative point {x=" + std::to_string(relPoint.x) + ", y=" + std::to_string(relPoint.y) + "} must be in [0, 1]");
	m_relPoints.push_back(relPoint);
}

const sf::Vector2f& PolygonShape::getPoint(int index) const
{
	if (index < 0 || index >= getNumOfPoints())
		throw std::out_of_range("Cannot find point at " + std::to_string(index));
	return m_relPoints[index];
}

string PolygonShape::toString() const
{
	return "PolygonShape: { " + Shape::toString() + " }";
}
