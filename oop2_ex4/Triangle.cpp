#include "Triangle.h"



Triangle::Triangle(const sf::Color& color, PointingSide pointingSide)
	:PolygonShape(color), m_pointingSide(pointingSide)
{
	init();
}

float Triangle::getWidth() const
{
	switch (m_pointingSide)
	{
		case PointingSide::UP:
		case PointingSide::DOWN:
			return abs(getPoint(1).x - getPoint(2).x);
		case PointingSide::LEFT:
		case PointingSide::RIGHT:
			return abs(getPoint(0).x - getPoint(1).x);
		}
	// for compiler
	return 0.0f;
}

float Triangle::getHeight() const
{
	switch (m_pointingSide)
	{
		case PointingSide::UP:
		case PointingSide::DOWN:
			return abs(getPoint(1).y - getPoint(2).y);
		case PointingSide::LEFT:
		case PointingSide::RIGHT:
			return abs(getPoint(0).y - getPoint(1).y);
	}
	// for compiler
	return 0.0f;
}

int Triangle::getNumOfEdges() const
{
	return NUM_OF_EDGES;
}

string Triangle::toString() const
{
	return "Trinangle: { " + PolygonShape::toString() + " }";
}

void Triangle::init()
{
	switch (m_pointingSide)
	{
		case PointingSide::UP:
			addPoint(sf::Vector2f(0.5f, 0.f));
			addPoint(sf::Vector2f(1.f, 1.f));
			addPoint(sf::Vector2f(0.f, 1.f));
			break;
		case PointingSide::DOWN:
			addPoint(sf::Vector2f(0.5f, 1.f));
			addPoint(sf::Vector2f(0.f, 0.f));
			addPoint(sf::Vector2f(1.f, 0.f));
			break;
		case PointingSide::LEFT:
			addPoint(sf::Vector2f(0.f, 0.5f));
			addPoint(sf::Vector2f(1.f, 0.f));
			addPoint(sf::Vector2f(1.f, 1.f));
			break;
		case PointingSide::RIGHT:
			addPoint(sf::Vector2f(1.f, 0.5f));
			addPoint(sf::Vector2f(0.f, 1.f));
			addPoint(sf::Vector2f(0.f, 0.f));
			break;
	}
}
