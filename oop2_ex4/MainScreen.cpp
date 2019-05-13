#include "MainScreen.h"

MainScreen::MainScreen(sf::RenderWindow& window)
	: GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>(window), m_menuTitle(std::make_shared<GUI::TextView>(window, "Welcome To Six Colors")),
		m_createGameBt(std::make_shared<GUI::Button>(window, "Create Game")),
		m_exitBt(std::make_shared<GUI::Button>(window, "Exit Game")),
		m_joinGameBt(std::make_shared<GUI::Button>(window, "Join Game")),
		m_singlePlayerBt(std::make_shared<GUI::Button>(window, "Single Player"))
{
	init();
}

string MainScreen::toString() const
{
	return "MainScreen: { " + GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>::toString() + " }";
}

void MainScreen::init()
{
	// init title
	m_menuTitle->setTextSize(30);	
	m_menuTitle->setTextColor(sf::Color(244, 226, 63));
	m_menuTitle->setTextStyle(sf::Text::Style::Underlined);
	m_menuTitle->setFont("BRLNSDB");
	addView(m_menuTitle, sf::FloatRect(1.f / 4.f, 0.05f, 1.f / 2.f, 0.10f));

	// init start game button
	m_singlePlayerBt->getBackground().setColor(sf::Color::Green);
	m_singlePlayerBt->setTextSize(20);
	m_singlePlayerBt->addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(255, 255, 255, 128));
	});
	m_singlePlayerBt->addLeaveListener(([this](View& view) {
		view.getBackground().setColor(sf::Color(sf::Color::Green));
	}));
	m_singlePlayerBt->setTextColor(sf::Color::Black);
	addView(m_singlePlayerBt, sf::FloatRect(2.f / 5.f, 0.25f, 1.f / 5.f, 0.10f));

	// init create game button
	m_createGameBt->getBackground().setColor(sf::Color::Yellow);
	m_createGameBt->setTextSize(20);
	m_createGameBt->addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(255, 255, 255, 128));
	});
	m_createGameBt->addLeaveListener(([this](View& view) {
		view.getBackground().setColor(sf::Color(sf::Color::Yellow));
	}));
	m_createGameBt->setTextColor(sf::Color::Black);
	addView(m_createGameBt, sf::FloatRect(2.f / 5.f, 0.45f, 1.f / 5.f, 0.10f));

	// init start game button
	m_joinGameBt->getBackground().setColor(sf::Color::Magenta);
	m_joinGameBt->setTextSize(20);
	m_joinGameBt->addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(255, 255, 255, 128));
	});
	m_joinGameBt->addLeaveListener(([this](View& view) {
		view.getBackground().setColor(sf::Color(sf::Color::Magenta));
	}));
	m_joinGameBt->setTextColor(sf::Color::Black);
	addView(m_joinGameBt, sf::FloatRect(2.f / 5.f, 0.65f, 1.f / 5.f, 0.10f));

	// init exit game button
	m_exitBt->getBackground().setColor(sf::Color::Red);
	m_exitBt->setTextSize(20);
	m_exitBt->addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(255, 255, 255, 128));
	});
	m_exitBt->addLeaveListener(([this](View& view) {
		view.getBackground().setColor(sf::Color(sf::Color::Red));
	}));
	m_exitBt->setTextColor(sf::Color::Black);
	addView(m_exitBt, sf::FloatRect(2.f / 5.f, 0.85f, 1.f / 5.f, 0.10f));
}