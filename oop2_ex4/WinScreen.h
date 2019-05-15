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
 * GameScreen class
 */
class winScreen
	: public BSWinScreen
{
public:
	// constructor
	explicit winScreen(sf::RenderWindow& window);
	//get buttons
	const std::shared_ptr<GUI::TextView>& getGameMenu() const { return m_titleTv; }
	//const std::shared_ptr<GUI::ImageView>& getBoard() const { return m_winImage; }
	const std::shared_ptr<GUI::Button>& getBottomPanel() const { return m_backMenuBt; }
	// destructor
	virtual ~winScreen() = default;
	// convert to string
	virtual string toString() const override;
private:
	std::shared_ptr<GUI::TextView> m_titleTv;
//	std::shared_ptr<GUI::ImageView> m_winImage;
	std::shared_ptr<GUI::Button> m_backMenuBt;
	// init
	void init();
};



