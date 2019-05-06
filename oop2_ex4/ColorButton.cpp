#include "ColorButton.h"


ColorButton::ColorButton(sf::RenderWindow& window, const sf::Color& color)
	: Button(window)
{
	setColor(color);
}

void ColorButton::setColor(const sf::Color& color)
{
	m_color = color;
	// change background to this color
	getBackground().setColor(m_color);
}

string ColorButton::toString() const
{
	return "ColorButton: { " + Button::toString() + ", Color: " + std::to_string(m_color.toInteger()) + " }";
}
