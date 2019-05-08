#pragma once
//---- include section ------
#include "Button.h"
#include <string>

//---- using section --------
using std::string;

/*
 * ColorButton class
 */
class ColorButton :
	public GUI::Button
{
public:
	// constructor
	explicit ColorButton(sf::RenderWindow& window, const sf::Color& color);
	// get color
	const sf::Color& getColor() const { return m_color; }
	// set color
	void setColor(const sf::Color& color);
	// convert to string
	virtual string toString() const override;
private:
	//init
	void init(const sf::Color& color);
	// color
	sf::Color m_color;
};

