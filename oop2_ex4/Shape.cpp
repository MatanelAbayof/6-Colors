#include "Shape.h"


Shape::Shape(const sf::Color& color)
{
	setColor(color);
}


string Shape::toString() const
{
	return "Shape: Width = " + std::to_string(getWidth()) + " Height: " + std::to_string(getHeight()) + " Num of edge: " + std::to_string(getNumOfEdges()) + " Color: " + std::to_string(m_color.toInteger());
}
