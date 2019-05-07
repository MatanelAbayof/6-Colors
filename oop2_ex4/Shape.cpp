#include "Shape.h"


Shape::Shape(float width, float height, const sf::Color & color)
{
	setWidth(width);
	setHeight(height);
	setColor(color);
}

void Shape::setWidth(float width)
{
	if (width < 0)
		throw std::length_error("Width " + std::to_string(width) + " not legal!");
	m_width = width;
}

void Shape::setHeight(float height)
{
	if (height < 0)
		throw std::length_error("Height " + std::to_string(height) + " not legal!");
	m_height = height;
}

string Shape::toString() const
{
	return "Shape: Width = " + std::to_string(m_width) + "Height: " + std::to_string(m_height) + "Num of edge: " + std::to_string(getNumOfEdges()) + "Color: " + std::to_string(m_color.toInteger());
}
