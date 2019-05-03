#include "GameMenu.h"


GameMenu::GameMenu(sf::RenderWindow& window) 
	: HorizontalLayout(window)
{
	initComponents(window);
}

string GameMenu::toString() const
{
	return "GameMenu: " + HorizontalLayout::toString();
}

void GameMenu::initComponents(sf::RenderWindow& window)
{
	// set my border & background
	getBorder().setColor(sf::Color::Black);
	getBackground().setColor(sf::Color(240, 255, 239));
	
	m_restart = std::make_shared<GUI::Button>(window, "restart");
	m_exit = std::make_shared<GUI::Button>(window, "exit");

	m_restart->getBackground().setColor(sf::Color::Blue);
	m_exit->getBackground().setColor(sf::Color::Red);
	// init buttons
	initButton(m_restart);
	initButton(m_exit);
}

void GameMenu::initButton(std::shared_ptr<GUI::Button> bt)
{
	bt->getBorder().setColor(sf::Color::Black);
	/*addEnterListener([bt](View &view) {
		bt->getBackground().setColor(sf::Color::Transparent);
	});
	addClickListener([bt](View &view) {
		bt->getBackground().setColor(sf::Color::Transparent);
	});*/
	float relativeSize = float(1.f / 5.f);
	addView(bt, relativeSize);
}
