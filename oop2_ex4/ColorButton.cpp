#include "ColorButton.h"

ColorButton::ColorButton(sf::RenderWindow& window, const sf::Color& color)
	: Button(window)
{
	init(color);
}

void ColorButton::setColor(const sf::Color& color)
{
	m_color = color;

	// change background to this color
	getBackground().setColor(m_color);
}

void ColorButton::enable()
{
	Button::enable();
	setText("");
	getBackground().setColor(m_color);
}

void ColorButton::disable()
{
	Button::disable();
	setText("X");
	getBackground().setColor(m_color);
}

string ColorButton::toString() const
{
	return "ColorButton: { " + Button::toString() + ", Color: " + std::to_string(m_color.toInteger()) + " }";
}

void ColorButton::init(const sf::Color& color)
{
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	setColor(color);
	setTextColor(sf::Color(116, 0, 0));
	setTextSize(50);
	setFont("david");

	// make dark color when mouse entered
	addEnterListener([color](View &view) {
		sf::Color c;
		if (color.r > 70)
			c.r = color.r - 70;
		else
			c.r = color.r;
		if (color.b > 70)
			c.b = color.b - 70;
		else
			c.b = color.b;
		if (color.g > 70)
			c.g = color.g - 70;
		else
			c.g = color.g;
		view.getBackground().setColor(c);
	});

	// return to regular color
	addLeaveListener([color](View &view) {
		view.getBackground().setColor(color);
	});
}
