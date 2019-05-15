#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "TextView.h"
#include "ImageView.h"
#include "Button.h"
#include "RelativeLayout.h"

//---- using section --------
using std::string;
using BSWinScreen = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;

/*
 * winScreen class
 */
class WinScreen
	: public BSWinScreen
{
public:
	// constructor
	explicit WinScreen(sf::RenderWindow& window);
	// get buttons
	const std::shared_ptr<GUI::TextView>& getTitleTV() const { return m_titleTv; }
	const std::shared_ptr<GUI::Button>& getBackToMenuBT() const { return m_backMenuBt; }
	// destructor
	virtual ~WinScreen() = default;
	// convert to string
	virtual string toString() const override;
private:
	std::shared_ptr<GUI::TextView> m_titleTv;
	std::shared_ptr<GUI::Button> m_backMenuBt;
	// init
	void init();
};



