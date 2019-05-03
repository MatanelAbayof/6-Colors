#include "ColorPanel.h"


ColorPanel::ColorPanel(sf::RenderWindow & window)
	: HorizontalLayout(window)
{
	initComponents(window);
}

string ColorPanel::toString() const
{
	return "ColorPanel: " + HorizontalLayout::toString();
}

void ColorPanel::initComponents(sf::RenderWindow & window)
{
	// set my border & background
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));

	//init ptr
	m_blue = std::make_shared<ColorButton>(window, sf::Color::Blue);
	m_green = std::make_shared<ColorButton>(window, sf::Color::Green);
	m_red = std::make_shared<ColorButton>(window, sf::Color::Red);
	m_yellow = std::make_shared<ColorButton>(window, sf::Color::Yellow);
	m_purple = std::make_shared<ColorButton>(window, sf::Color(82, 67, 170));
	m_orange = std::make_shared<ColorButton>(window, sf::Color(255, 139, 0));

	//init button
	initButton(m_blue);
	initButton(m_green);
	initButton(m_red);
	initButton(m_yellow);
	initButton(m_purple);
	initButton(m_orange);
}

void ColorPanel::initButton(std::shared_ptr<ColorButton> bt)
{
	bt->getBackground().setColor(bt->getColor());
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	float relativeSize = float(1.f / 6.f);
	addView(bt, relativeSize);
}

