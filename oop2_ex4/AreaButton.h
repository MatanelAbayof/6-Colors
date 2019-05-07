#pragma once
//---- include section ------
#include <string>
#include "TextView.h"
//---- using section --------
using std::string;

/*
 * AreaButtun class
 */
class AreaButton :
	public GUI::TextView
{
public:
	// constructor
	AreaButton(sf::RenderWindow& window, float areaPercent = 0);
	//get area percent
	float getAreaPercent();
	//set pre text
//	void setPreText(string text) const { m_text. text; }
	//set areaPercent
	void setAreaPercent(float area);
	// convert to string
	virtual string toString() const;
private:
	//init
	void init();
	//mt text
	string m_text;
	// quantity of area in percent
	float m_areaPercent;
};


