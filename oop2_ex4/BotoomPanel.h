#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "View.h"
#include "ColorPanel.h"
#include "TextView.h"

//---- using section --------
using std::string;

/*
 * BotoomPanel class
 */
class BotoomPanel :
	public GUI::HorizontalLayout<GUI::View>
{
public:
	// constructor
	BotoomPanel(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const;
protected:
	//init
	void initComponents(sf::RenderWindow& window);
	//init button
	void initButton(std::shared_ptr<GUI::View> bt);

private:
	std::shared_ptr<ColorPanel> m_colorPanel;
	std::shared_ptr<GUI::TextView> m_myArea, m_rivalArea, m_turn;


};

