#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "TextView.h"

//---- using section --------
using std::string;

/*
 * WaitingMultiplayerScreen class
 */

class WaitingMultiplayerScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	WaitingMultiplayerScreen(sf::RenderWindow& window);
	~WaitingMultiplayerScreen();
private:
	// waiting and IP signs
	std::shared_ptr<GUI::TextView> m_waitingToClientTv, m_myIpTv;
	// start button
	std::shared_ptr<GUI::Button> m_startBt;
	// init buttons
	void init();
};

