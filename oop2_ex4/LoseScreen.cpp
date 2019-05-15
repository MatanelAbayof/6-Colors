#include "LoseScreen.h"

LoseScreen::LoseScreen(sf::RenderWindow & window)
	: BSLoseScreen(window), m_titleTv(std::make_shared<GUI::TextView>(window, "You lose!!!")),
	m_loseImage(std::make_shared<GUI::ImageView>(window)),
	m_backMenuBt(std::make_shared<GUI::Button>(window, "Back to menu"))
{
	init();
}

string LoseScreen::toString() const
{
	return "LoseScreen: { " + BaseScreen::toString() + " }";;
}

void LoseScreen::init()
{
	//m_winImage->getImage().setTexture("win");
	getBackground().setColor(sf::Color::Cyan);
	
	// init title
	m_titleTv->setTextColor(sf::Color(0, 102, 0));
	m_titleTv->setTextSize(70);
	m_titleTv->getBackground().setColor(sf::Color::Transparent);
	addView(m_titleTv, sf::FloatRect(1.f / 4.f, 0.05f, 1.f / 2.f, 0.10f));

	//init image
	m_loseImage->getImage().setTexture("lose");
	addView(m_loseImage, sf::FloatRect(1.f / 5.f, 0.2f, 3.f / 5.f, 0.55f));

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
	addView(m_backMenuBt, sf::FloatRect(2.f / 5.f, 0.75f, 1.f / 5.f, 0.15f));
}
