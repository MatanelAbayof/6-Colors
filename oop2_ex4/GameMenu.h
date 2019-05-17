#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "Button.h"
#include "TextView.h"

//---- using section --------
using std::string;
/*
 * GameMenu class
 */
class GameMenu :
	public GUI::HorizontalLayout<GUI::View>
{
public:
	// constructor
	explicit GameMenu(sf::RenderWindow& window);
	// get restart button
	const std::shared_ptr<GUI::Button>& getRestartButton() const { return m_restartBt; }
	// get exit button
	const std::shared_ptr<GUI::Button>& getExitButton() const { return m_exitBt; }
	// get turn button
	const std::shared_ptr<GUI::TextView>& getTurnButton() const { return m_turnTv; }
	// convert to string
	virtual string toString() const override;
private:
	// buttons
	std::shared_ptr<GUI::Button> m_restartBt, m_exitBt;
	// turn button
	std::shared_ptr<GUI::TextView> m_turnTv;
	// init components
	void initComponents(sf::RenderWindow& window);
	// init button
	void initButton(std::shared_ptr<GUI::Button> bt);
};
