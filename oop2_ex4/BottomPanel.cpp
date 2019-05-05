#include "BottomPanel.h"

BottomPanel::BottomPanel(sf::RenderWindow & window)
	: HorizontalLayout(window)
{
	initComponents(window);
}

string BottomPanel::toString() const
{
	return "BottomPanel: { " + HorizontalLayout::toString() + " }";
}

void BottomPanel::initComponents(sf::RenderWindow & window)
{
	// set my border & background
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));

	//init ptr
	m_colorPanel = std::make_shared<ColorPanel>(window);
	m_myArea = std::make_shared<GUI::TextView>(window, "MyArea");
	m_rivalArea = std::make_shared<GUI::TextView>(window, "RivalArea");
	m_turn = std::make_shared<GUI::TextView>(window, "Turn");

	//init button
	initButton(m_myArea);
	initButton(m_colorPanel);
	initButton(m_turn);
	initButton(m_rivalArea);
}

void BottomPanel::initButton(std::shared_ptr<GUI::View> bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	float relativeSize = float(1.f / 6.f);
	addView(bt, relativeSize);
}
