#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "TextView.h"
#include "AnimationView.h"

//---- using section --------
using std::string;

/*
 * WaitingMultiplayerScreen class
 */
class WaitingMultiplayerScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// constructor
	explicit WaitingMultiplayerScreen(sf::RenderWindow& window);
	// get load animation
	const std::shared_ptr<GUI::AnimationView>& getLoadAnimation() const { return m_loadAv; };
	// get start button
	const std::shared_ptr<GUI::Button>& getStartButton() const { return m_startBt; }
private:
	// waiting and IP signs
	std::shared_ptr<GUI::TextView> m_waitingToClientTv, m_myIpTv;
	// load animation
	std::shared_ptr<GUI::AnimationView> m_loadAv;
	// start button
	std::shared_ptr<GUI::Button> m_startBt;
	// init buttons
	void init();
};

