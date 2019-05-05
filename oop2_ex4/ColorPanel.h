#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "ColorButton.h"

//---- using section --------
using std::string;

/*
 * ColorPanel class
 */
class ColorPanel :
	public GUI::HorizontalLayout<ColorButton>
{
public:
	// constructor
	ColorPanel(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const;
protected:
	//init
	void initComponents(sf::RenderWindow& window);
	//init button
	void initButton(std::shared_ptr<ColorButton> bt);

private:
	std::shared_ptr<ColorButton> m_blue, m_green, m_red,
		                         m_yellow, m_purple, m_orange;

};


