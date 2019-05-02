#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>

//---- using section --------
using std::string;

namespace GUI {
/*
 * ImageTexture class
 */
class ImageTexture
{
public:
	// constructors
	ImageTexture();
	explicit ImageTexture(const sf::Color& color);
	explicit ImageTexture(sf::Texture& texture);
	explicit ImageTexture(const string& textureName);
	// copy constructor
	ImageTexture(const ImageTexture& other);
	// load mode options
	enum LoadMode {
		TEXTURE, COLOR
	};
	// get load mode
	LoadMode getLoadMode() const;
	// set texture
	void setTexture(const sf::Texture& texture);
	void setTexture(const string& textureName);
	// set color
	void setColor(const sf::Color& color);
	// update bounds
	void updateBounds(const sf::FloatRect& bounds);
	// draw
	void draw(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const;
private:
	// load mode of image texture 
	LoadMode m_loadMode;
	// last bounds
	sf::FloatRect m_bounds;
	// rectangle of color
	std::unique_ptr<sf::RectangleShape> m_rectColor; // saved in unique_ptr to save memory
	// sprite of texture
	std::unique_ptr <sf::Sprite> m_spriteTexture; // saved in unique_ptr to save memory
};
}
