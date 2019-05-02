#pragma once
//---- include section ------
#include <string>
#include "TextView.h"

//---- using section --------
using std::string;
using sf::Text;

namespace GUI {
/*
 * Button class
 */
class Button :
	public TextView
{
public:
	// constructor
	explicit Button(sf::RenderWindow& window, const string& text = "");
	// convert to string
	virtual string toString() const override;
private:
	// init components
	void initComponents();
};
}
