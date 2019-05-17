#include "BottomPanel.h"
#include <iomanip>

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

	// init ptr
	m_colorPanel = std::make_shared<ColorPanel>(window);
	m_myArea = std::make_shared<AreaButton>(window);
	m_rivalArea = std::make_shared<AreaButton>(window);

	// init text
	m_myArea->setPreText("My " + m_myArea->getPreText());
	m_rivalArea->setPreText("Rival " + m_rivalArea->getPreText());
	m_myArea->setText(m_myArea->getPreText() + std::to_string(m_myArea->getAreaPercent()) + "%");
	m_rivalArea->setText(m_rivalArea->getPreText() + std::to_string(m_myArea->getAreaPercent()) + "%");
	
	// init button
	initButton(m_myArea);
	initColorPanel(m_colorPanel);
	initButton(m_rivalArea);
}

void BottomPanel::initButton(const std::shared_ptr<AreaButton>& bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	bt->getBackground().setColor(sf::Color::Cyan);
	bt->setTextHAlignment(GUI::TextView::TextHAlignment::CENTER);
	float relativeSize = 0.2f;
	addView(bt, relativeSize);
}

void BottomPanel::initColorPanel(const std::shared_ptr<ColorPanel>& bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	float relativeSize = 0.6f;
	addView(bt, relativeSize);
}
