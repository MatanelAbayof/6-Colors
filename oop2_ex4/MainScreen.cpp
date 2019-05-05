#include "MainScreen.h"

GUI::MainScreen::MainScreen(sf::RenderWindow& window)
	:BaseScreen(window), m_menuTitle(std::make_shared<TextView>(window, "Six Colors")), 
	m_createGameBt(std::make_shared<Button>(window, "Create Game")), 
	m_exitBt(std::make_shared<Button>(window, "Exit Game")), 
	m_joinGameBt(std::make_shared<Button>(window, "Join Game")), 
	m_singlePlayerBt(std::make_shared<Button>(window, "Single Player"))
{
	init();
}

const std::shared_ptr<GUI::Button>& GUI::MainScreen::getSingleBt()
{
	return m_singlePlayerBt;
}

const std::shared_ptr<GUI::Button>& GUI::MainScreen::getCreateBt()
{
	return m_createGameBt;
}

const std::shared_ptr<GUI::Button>& GUI::MainScreen::getJoinBt()
{
	return m_joinGameBt;
}

const std::shared_ptr<GUI::Button>& GUI::MainScreen::getExitleBt()
{
	return m_exitBt;
}

string GUI::MainScreen::toString() const
{
	return "MainScreen: { " + BaseScreen::toString() + " }";
}

void GUI::MainScreen::init()
{
	// init title
	m_menuTitle->setTextColor(sf::Color::Cyan);
	m_menuTitle->setTextSize(20.f);
	addView(m_menuTitle, sf::FloatRect(2.f / 5.f, 0.05f, 1.f / 5.f, 0.10f));

	// init start game button
	m_singlePlayerBt->getBackground().setColor(sf::Color::Green);
	m_singlePlayerBt->setTextColor(sf::Color::White);
	m_singlePlayerBt->setTextSize(20.f);
	m_singlePlayerBt->addClickListener([this](View& view) {
		getWindow().close();
	});
	addView(m_singlePlayerBt, sf::FloatRect(2.f / 5.f, 0.25f, 1.f / 5.f, 0.10f));

	// init create game button
	m_createGameBt->getBackground().setColor(sf::Color::Yellow);
	m_createGameBt->setTextColor(sf::Color::White);
	m_createGameBt->setTextSize(20.f);
	m_createGameBt->addClickListener([this](View& view) {
		getWindow().close();
	});
	addView(m_createGameBt, sf::FloatRect(2.f / 5.f, 0.45f, 1.f / 5.f, 0.10f));

	// init start game button
	m_joinGameBt->getBackground().setColor(sf::Color::Magenta);
	m_joinGameBt->setTextColor(sf::Color::White);
	m_joinGameBt->setTextSize(20.f);
	m_joinGameBt->addClickListener([this](View& view) {
		getWindow().close();
	});
	addView(m_joinGameBt, sf::FloatRect(2.f / 5.f, 0.65f, 1.f / 5.f, 0.10f));

	// init exit game button
	m_exitBt->getBackground().setColor(sf::Color::Red);
	m_exitBt->setTextColor(sf::Color::White);
	m_exitBt->setTextSize(20.f);
	m_exitBt->addClickListener([this](View& view) {
		getWindow().close();
	});
	addView(m_exitBt, sf::FloatRect(2.f / 5.f, 0.85f, 1.f / 5.f, 0.10f));
}

