#include "JoinGameScreen.h"
#include <regex>

// init
const sf::Color JoinGameScreen::ENTERED_CONNECT_BT_COLOR(1, 137, 63),
                JoinGameScreen::CONNECT_BT_COLOR(0, 176, 80),
	            JoinGameScreen::DISABLED_CONNECT_BT_COLOR(170, 170, 170);

JoinGameScreen::JoinGameScreen(sf::RenderWindow& window)
	: JoinGameBaseScreen(window)
{
	initComponents();
}

string JoinGameScreen::toString() const
{
	return "JoinGameScreen: { " + JoinGameBaseScreen::toString() + " }";
}

void JoinGameScreen::initComponents()
{
	// create enter IP text view
	m_enterIpTv = std::make_shared<GUI::TextView>(getWindow(), "Please enter an IP:");
	m_enterIpTv->setTextHAlignment(GUI::TextView::TextHAlignment::CENTER);
	m_enterIpTv->setTextColor(sf::Color(51, 63, 80));
	m_enterIpTv->setTextSize(40);
	m_enterIpTv->setFont("BRLNSDB");
	addView(m_enterIpTv, sf::FloatRect(0.1f, 0.f, 0.8f, 0.3f));

	// create IP edit text
	m_ipEt = std::make_shared<GUI::EditText>(getWindow());
	m_ipEt->setTextColor(sf::Color(32, 56, 100));
	m_ipEt->setFont("BAUHS93");
	m_ipEt->setTextSize(35);
	addView(m_ipEt, sf::FloatRect(0.1f, 0.12f, 0.8f, 0.3f));

	// create connect button
	m_connectBt = std::make_shared<GUI::Button>(getWindow(), "Connect");
	m_connectBt->setTextSize(30);
	m_connectBt->setTextColor(sf::Color::White);
	m_connectBt->disable();
	m_connectBt->getBackground().setColor(JoinGameScreen::DISABLED_CONNECT_BT_COLOR);
	m_connectBt->addEnterListener([](View& view) {
		view.getBackground().setColor(JoinGameScreen::ENTERED_CONNECT_BT_COLOR);
	});
	m_connectBt->addLeaveListener([](View& view) {
		view.getBackground().setColor(JoinGameScreen::CONNECT_BT_COLOR);
	});
	addView(m_connectBt, sf::FloatRect(0.4f, 0.8f, 0.2f, 0.12f));

	// listen IP keyboard
	m_ipEt->addKeyDownListener([this](sf::Keyboard::Key& key) {
		if (isLegalIP(m_ipEt->getText())) {
			m_connectBt->enable();
			m_connectBt->getBackground().setColor(JoinGameScreen::CONNECT_BT_COLOR);
		}
		else {
			m_connectBt->disable();
			m_connectBt->getBackground().setColor(JoinGameScreen::DISABLED_CONNECT_BT_COLOR);
		}
	});
	m_ipEt->startRecordText();
}

bool JoinGameScreen::isLegalIP(const string& ipAddress) const
{
	// create IP pattern
	string pattern = "\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b";
	std::regex re(pattern);
	return std::regex_match(ipAddress, re); // match IP
}
