#pragma once
//---- include section ------
#include <string>
#include <memory>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "TextView.h"
#include "EditText.h"

//---- using section --------
using std::string;
using JoinGameBaseScreen = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;

/*
 * MainScreen class
 */
class JoinGameScreen : public JoinGameBaseScreen
{
public:
	// constructor
	explicit JoinGameScreen(sf::RenderWindow& window);
	// destructor
	virtual ~JoinGameScreen() = default;
	// get IP edit text
	const std::shared_ptr<GUI::EditText>& getIpEditText() const { return m_ipEt; }
	// get connect button
	const std::shared_ptr<GUI::Button>& getConnectButton() const { return m_connectBt; }
	// convert to string
	virtual string toString() const override;
private:
	// colors of connect button
	static const sf::Color ENTERED_CONNECT_BT_COLOR, CONNECT_BT_COLOR, DISABLED_CONNECT_BT_COLOR;
	// enter IP text view
	std::shared_ptr<GUI::TextView> m_enterIpTv;
	// IP edit text
	std::shared_ptr<GUI::EditText> m_ipEt;
	// connect button
	std::shared_ptr<GUI::Button> m_connectBt;
	// init components
	void initComponents();
	// check if ipv4 is legal
	bool isLegalIP(const string& ipAddress) const;
};

