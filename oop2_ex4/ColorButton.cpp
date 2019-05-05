#include "ColorButton.h"


ColorButton::ColorButton(sf::RenderWindow& window, const sf::Color& color)
	: Button(window)
{
	setColor(color);
}

const sf::Color& ColorButton::getColor() const
{
	return m_color;
}

void ColorButton::setColor(const sf::Color& color)
{
	m_color = color;
	getBackground().setColor(m_color);
}

string ColorButton::toString() const
{
	return "ColorButton: " + Button::toString() + "Color: " + std::to_string(m_color.toInteger());
}
