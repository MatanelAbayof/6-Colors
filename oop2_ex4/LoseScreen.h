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
using BSLoseScreen = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;

/*
 * LoseScreen class
 */
class LoseScreen
	: public BSLoseScreen
{
public:
	// constructor
	explicit LoseScreen(sf::RenderWindow& window);
	//get buttons
	const std::shared_ptr<GUI::TextView>& getGameMenu() const { return m_titleTv; }
	const std::shared_ptr<GUI::ImageView>& getBoard() const { return m_loseImage; }
	const std::shared_ptr<GUI::Button>& getBottomPanel() const { return m_backMenuBt; }
	// destructor
	virtual ~LoseScreen() = default;
	// convert to string
	virtual string toString() const override;
private:
	std::shared_ptr<GUI::TextView> m_titleTv;
	std::shared_ptr<GUI::ImageView> m_loseImage;
	std::shared_ptr<GUI::Button> m_backMenuBt;
	// init
	void init();
};


