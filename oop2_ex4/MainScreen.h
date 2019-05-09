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
 * MainScreen class
 */
class MainScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// constructor
	explicit MainScreen(sf::RenderWindow& window);
	// destructor
	~MainScreen() = default;
	// get certin button
	const std::shared_ptr<GUI::Button>& getSingleBt() const { return m_singlePlayerBt; }
	const std::shared_ptr<GUI::Button>& getCreateBt() const { return m_createGameBt; }
	const std::shared_ptr<GUI::Button>& getJoinBt() const { return m_joinGameBt; }
	const std::shared_ptr<GUI::Button>& getExitleBt() const { return m_exitBt; }
	// convert to string
	virtual string toString() const override;
private:
	// menu title
	std::shared_ptr<GUI::TextView> m_menuTitle;
	// buttons
	std::shared_ptr<GUI::Button> m_singlePlayerBt, m_createGameBt, m_joinGameBt, m_exitBt;
	// init buttons
	void init();
};
