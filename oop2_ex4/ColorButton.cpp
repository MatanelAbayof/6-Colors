#include "ColorButton.h"


ColorButton::ColorButton(sf::RenderWindow& window, const sf::Color& color)
	: Button(window)
{
	setColor(color);
}

sf::Color ColorButton::getColor() const
{
	return m_color;
}

void ColorButton::setColor(const sf::Color& color)
{
	m_color = color;
}

string ColorButton::toString() const
{
	return "ColorButton: " + Button::toString();
}
