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
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));
	
	m_restartBt->getBackground().setColor(sf::Color::Blue);
	m_exitBt->getBackground().setColor(sf::Color::Red);

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
	/*addEnterListener([bt](View &view) {
		bt->getBackground().setColor(sf::Color::Transparent);
	});
	addClickListener([bt](View &view) {
		bt->getBackground().setColor(sf::Color::Transparent);
	});*/
}
