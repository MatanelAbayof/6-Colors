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
	const std::shared_ptr<GUI::TextView>& getTitleTV() const { return m_titleTv; }
	const std::shared_ptr<GUI::ImageView>& getLoseImage() const { return m_loseImage; }
	const std::shared_ptr<GUI::Button>& getBackToMenuBT() const { return m_backMenuBt; }
	// destructor
	virtual ~LoseScreen() = default;
	// convert to string
	virtual string toString() const override;
private:
	// title text view
	std::shared_ptr<GUI::TextView> m_titleTv;
	// lose image view
	std::shared_ptr<GUI::ImageView> m_loseImage;
	// back to menu button
	std::shared_ptr<GUI::Button> m_backMenuBt;
	// init
	void init();
};


