#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "Button.h"

//---- using section --------
using std::string;

/*
 * GameMenu class
 */
class GameMenu :
	public GUI::HorizontalLayout<GUI::Button>
{
public:
	// constructor
	GameMenu(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const;
protected:
	//init
	void initComponents(sf::RenderWindow& window);
	//init button
	void initButton(std::shared_ptr<GUI::Button> bt);
private:
	std::shared_ptr<GUI::Button> m_restart, m_exit;

};

