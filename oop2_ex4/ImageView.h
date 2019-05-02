#pragma once
//---- include section ------
#include "View.h"
#include <string>

//---- using section --------
using std::string;

namespace GUI {
class ImageView :
	public View
{
public:
	// constructor
	explicit ImageView(sf::RenderWindow& window);
	// get image
	ImageTexture& getImage();
	// draw in window
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents();
private:
	// image texture
	ImageTexture m_image;
};
}
