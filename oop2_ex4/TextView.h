#pragma once
//---- include section ------
#include <string>
#include "View.h"

//---- using section --------
using std::string;

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
	// set text style (use with sf::Text::Style)
	void setTextStyle(sf::Uint32 style);
	// get text style
	sf::Uint32 getTextStyle() const { return m_text.getStyle(); }
	// draw
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
private:
	// text object
	sf::Text m_text;
	// text color
	sf::Color m_textColor;
	// text horizonal alignment
	TextHAlignment m_textHAlign;
};
}
