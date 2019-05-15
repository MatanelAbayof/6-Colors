#include "WinScreen.h"

WinScreen::WinScreen(sf::RenderWindow & window)
	: BSWinScreen(window), m_titleTv(std::make_shared<GUI::TextView>(window, "You win!!!")),
	m_backMenuBt(std::make_shared<GUI::Button>(window, "Back to menu"))
{
	init();
}

string WinScreen::toString() const
{
	return "WinScreen: { " + BaseScreen::toString() + " }";
}

void WinScreen::init()
{	
	getBackground().setTexture("win");

	// init title
	m_titleTv->setTextColor(sf::Color(0, 102, 0));
	m_titleTv->setTextSize(70);
	m_titleTv->getBackground().setColor(sf::Color::Transparent);
	addView(m_titleTv, sf::FloatRect(1.f / 4.f, 0.05f, 1.f / 2.f, 0.10f));

	// init back to menu button
	m_backMenuBt->getBackground().setColor(sf::Color::Blue);
	m_backMenuBt->setTextSize(25);
	m_backMenuBt->setTextColor(sf::Color::White);
	m_backMenuBt->setTextStyle(sf::Text::Style::Bold);
	m_backMenuBt->addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(0, 0, 102));
	});
	m_backMenuBt->addLeaveListener(([this](View& view) {
		view.getBackground().setColor(sf::Color(sf::Color::Blue));
	}));

	addView(m_backMenuBt, sf::FloatRect(2.f / 5.f, 0.65f, 1.f / 5.f, 0.15f));
}
