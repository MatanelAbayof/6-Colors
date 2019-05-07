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
	explicit AreaButton(sf::RenderWindow& window, const string& text = "", float areaPercent = 0);
	//get area percent
	float& getAreaPercent();
	//set areaPercent
	void setAreaPercent(float area);
	// convert to string
	virtual string toString() const;
private:
	// quantity of area in percent
	float m_areaPercent;
};


