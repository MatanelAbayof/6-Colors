#pragma once
//---- include section ------
#include <string>
#include "View.h"

//---- using section --------
using std::string;
using sf::Text;

namespace GUI {
/*
 * TextView class
 */
class TextView : public GUI::View
{
public:
	// text horizontal alignment
	enum TextHAlignment {
		RIGHT, CENTER, LEFT
	};
	// constructor
	explicit TextView(sf::RenderWindow& window, const string& text = "");
	// get text
	string getText() const;
	// set text
	void setText(const string& text);
	// append text
	void appendText(const string& text);
	// set text color
	void setTextColor(const sf::Color& textColor);
	// get text color
	sf::Color getTextColor() const;
	// set font
	void setFont(const sf::Font& font);
	void setFont(const string& fontName);
	// set text horizontal alignment
	void setTextHAlignment(TextHAlignment textHAlign);
	// set text size
	void setTextSize(unsigned int textSize);
	// get text size
	unsigned int getTextSize() const;
	// get text horizontal alignment
	TextHAlignment getTextHAlignment() const;
	// set text style
	void setTextStyle(sf::Text::Style style);
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
private:
	// text object
	Text m_text;
	// text color
	sf::Color m_textColor;
	// text horizonal alignment
	TextHAlignment m_textHAlign;
};
}
