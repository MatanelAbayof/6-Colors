#include "BotoomPanel.h"

BotoomPanel::BotoomPanel(sf::RenderWindow & window)
	: HorizontalLayout(window), m_myAreaPercent(0), m_rivalAreaPercent(0)
{
	initComponents(window);
}

string BotoomPanel::toString() const
{
	return "BotoomPanel: " + HorizontalLayout::toString();
}

void BotoomPanel::initComponents(sf::RenderWindow & window)
{
	// set my border & background
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));

	//init ptr
	m_colorPanel = std::make_shared<ColorPanel>(window);
	m_myArea = std::make_shared<GUI::TextView>(window, "MyArea");
	m_rivalArea = std::make_shared<GUI::TextView>(window, "RivalArea");

	//init button
	initButton(m_myArea);
	initColorPanel(m_colorPanel);
	initButton(m_rivalArea);
}

void BotoomPanel::initButton(std::shared_ptr<GUI::TextView> bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	bt->getBackground().setColor(sf::Color::Cyan);
	bt->appendText(":\n10%");
	bt->setTextHAlignment(GUI::TextView::TextHAlignment::CENTER);
	float relativeSize = 0.2f;
	addView(bt, relativeSize);
}

void BotoomPanel::initColorPanel(std::shared_ptr<ColorPanel> bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	float relativeSize = 0.6f;
	addView(bt, relativeSize);
}
