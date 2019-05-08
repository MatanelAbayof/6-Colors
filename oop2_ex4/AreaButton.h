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
	void setPreText(const string& text) { m_preText.setString(text); }
	string getPreText() { return m_preText.getString(); }
	//set areaPercent
	void setAreaPercent(float area);
	// convert to string
	virtual string toString() const;
private:
	//init
	void init();
	//pre text
	sf::Text m_preText;
	// quantity of area in percent
	float m_areaPercent;
};


