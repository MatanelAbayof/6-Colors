#include "Square.h"

Square::Square(const sf::Color& color)
	: PolygonShape(color)
{
	init();
}

string Square::toString() const
{
	return "Square: " + Shape::toString();
}

void Square::init()
{
	addPoint(sf::Vector2f(0.5f, 0.f));
	addPoint(sf::Vector2f(1.f, 0.5f));
	addPoint(sf::Vector2f(0.5f, 1.f));
	addPoint(sf::Vector2f(0.f, 0.5f));
}
