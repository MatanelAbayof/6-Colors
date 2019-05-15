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
	explicit AreaButton(sf::RenderWindow& window, float areaPercent = 0.f);
	//get area percent
	float getAreaPercent() const;
	//set pre text
	void setPreText(const string& text) { m_preText = text; }
	const string& getPreText() const { return m_preText; }
	//set areaPercent
	void setAreaPercent(float area);
	// update area percent
	void updateAreaPercent(int MyShape, int numOfAllshapes);
	// convert to string
	virtual string toString() const override;
private:
	//init
	void init();
	//pre text
	string m_preText;
	// quantity of area in percent
	float m_areaPercent;
};


