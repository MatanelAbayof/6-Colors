#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

//---- using section --------
using std::string;

namespace GUI {
/*
 * Border class
 */
class Border
{
public:
	// constructor (0 - no border)
	explicit Border(const sf::Color& color = sf::Color(), float size = 0);
	// copy constructor
	Border(const Border& other);
	// set color
	void setColor(const sf::Color& color);
	// get color
	const sf::Color& getColor() const { return m_color; }
	// set size
	void setSize(float size);
	// get size
	float getSize() const { return m_size; }
	// update bounds
	void updateBounds(const sf::FloatRect& bounds);
	// draw
	void draw(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const;
private:
	// rectangle of color
	std::unique_ptr<sf::RectangleShape> m_rectBorder; // saved in unique_ptr to save memory
	// bounds
	sf::FloatRect m_bounds;
	// color
	sf::Color m_color;
	// size
	float m_size;
	// create and initialize rectangle shape
	void createRectShape();
	// delete rectangle
	void deleteRectShape() { m_rectBorder.release(); }
	// check if rectangle is initialized
	bool isRectInit() const { return bool(m_rectBorder); }
};
}
