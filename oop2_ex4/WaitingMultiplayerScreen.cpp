#include "WaitingMultiplayerScreen.h"



WaitingMultiplayerScreen::WaitingMultiplayerScreen(sf::RenderWindow& window)
	: GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>(window), m_waitingToClientTv(std::make_shared<GUI::TextView>(window, "Waiting For The Other Player...")),
	m_myIpTv(std::make_shared<GUI::TextView>(window, "My Ip: ")),
	m_startBt(std::make_shared<GUI::Button>(window, "Start Game"))
{
	init();
}


WaitingMultiplayerScreen::~WaitingMultiplayerScreen()
{
}

void WaitingMultiplayerScreen::init()
{
	// init waiting to client title
	m_waitingToClientTv->setTextColor(sf::Color::Cyan);
	m_waitingToClientTv->setTextSize(30);
	m_waitingToClientTv->setTextColor(sf::Color::Black);
	m_waitingToClientTv->setTextStyle(sf::Text::Style::Underlined);
	m_waitingToClientTv->setFont("BRLNSDB");
	addView(m_waitingToClientTv, sf::FloatRect(1.f / 4.f, 0.05f, 1.f / 2.f, 0.10f));

	// init my ip title 
	m_myIpTv->setTextColor(sf::Color::Cyan);
	m_myIpTv->setTextSize(30);
	m_myIpTv->setTextColor(sf::Color::Black);
	m_myIpTv->setTextStyle(sf::Text::Style::Bold);
	m_myIpTv->setFont("BAUHS93");
	addView(m_myIpTv, sf::FloatRect(2.f / 5.f, 0.60f, 1.f / 5.f, 0.10f));

	// init start game button
	m_startBt->getBackground().setColor(sf::Color::Green);
	m_startBt->setTextColor(sf::Color::White);
	m_startBt->setTextSize(20);
	m_startBt->setTextStyle(sf::Text::Style::Bold);
	m_startBt->addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(255, 255, 255, 128));
	});
	m_startBt->addLeaveListener(([this](View& view) {
		view.getBackground().setColor(sf::Color(sf::Color::Green));
	}));
	m_startBt->setTextColor(sf::Color::Black);
	addView(m_startBt, sf::FloatRect(2.f / 5.f, 0.75f, 1.f / 5.f, 0.10f));
}
