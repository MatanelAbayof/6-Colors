#include "GameMenu.h"


GameMenu::GameMenu(sf::RenderWindow& window) 
	: HorizontalLayout(window), m_restartBt(std::make_shared<GUI::Button>(window, "Restart")),
                                m_exitBt(std::make_shared<GUI::Button>(window, "Exit")),
	                            m_turnTv(std::make_shared<GUI::TextView>(window))
{
	initComponents(window);
}

string GameMenu::toString() const
{
	return "GameMenu: { " + HorizontalLayout::toString() + " }";
}

void GameMenu::initComponents(sf::RenderWindow& window)
{
	// set my border & background
	sf::Color restartBtColor(58, 123, 255), restartBtHoverColor(39, 80, 162),
		      exitBtColor(243, 3, 3), exitBtHoverColor(177, 8, 8);
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));
	
	m_restartBt->getBackground().setColor(restartBtColor);
	m_exitBt->getBackground().setColor(sf::Color::Red);

	m_restartBt->addEnterListener([restartBtHoverColor](View& view) {
		view.getBackground().setColor(restartBtHoverColor);
	});
	m_restartBt->addLeaveListener([restartBtColor](View& view) {
		view.getBackground().setColor(restartBtColor);
	});
	m_exitBt->addEnterListener([exitBtHoverColor](View& view) {
		view.getBackground().setColor(exitBtHoverColor);
	});
	m_exitBt->addLeaveListener([exitBtColor](View& view) {
		view.getBackground().setColor(exitBtColor);
	});

	m_turnTv->setFont("BAUHS93");
	m_turnTv->setTextSize(23);

	// init buttons
	initButton(m_restartBt);
	initButton(m_exitBt);

	addView(m_exitBt, 1.f / 7.f);
	addView(m_turnTv, 5.f / 7.f);
	addView(m_restartBt, 1.f / 7.f);
}

void GameMenu::initButton(std::shared_ptr<GUI::Button> bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	bt->getBorder().setSize(1.f);
	bt->setTextSize(20);
}
