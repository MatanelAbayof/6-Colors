#pragma once
//---- include section ------
#include <string>
#include <memory>
#include "HorizontalLayout.h"
#include "ImageView.h"
#include "TextView.h"

//---- using section --------
using std::string;

namespace GUI {
/*
 * ImageButtom class
 */
class ImageButton :
	public HorizontalLayout<GUI::View>
{
public:
	// constructor
	explicit ImageButton(sf::RenderWindow& window, const string& text = "");
	// get image
	ImageTexture& getImage();
	// set font
	void setFont(const string& fontName) { m_text->setFont(fontName); }
	// set text
	void setText(const string& text);
	// set text size
	void setTextSize(unsigned int textSize) { m_text->setTextSize(textSize); }
	// get text size
	unsigned int getTextSize() const { return m_text->getTextSize(); }
	// get text
	string getText() const;
	// set text colot
	void setTextColor(const sf::Color& textColor);
	// get text color
	sf::Color getTextColor() const;
	// set text horizontal alignment
	void setTextHAligment(TextView::TextHAlignment textAlignment);
	// convert to string
	virtual string toString() const override;
private:
	// image
	std::shared_ptr<ImageView> m_image;
	// text
	std::shared_ptr<TextView> m_text;
	// init components
	void initComponents(sf::RenderWindow& window, const string& text);
	// redeclaring scope of base class functions in private section of derived class
	using HorizontalLayout<GUI::View>::addView;
	using HorizontalLayout<GUI::View>::removeView;
};
}
