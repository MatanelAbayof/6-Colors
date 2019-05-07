#pragma once
//---- include section ------
#include <string>
#include <SFML/Graphics.hpp>

//---- using section --------
using std::string;

/*
 * Shape class
 */
class Shape
{
public:
	// constructor
	Shape(const sf::Color& color = sf::Color::Transparent);
	//set color
	void setColor(const sf::Color& color) { m_color = color; }
	//get width
	virtual float getWidth() const = 0;
	//get height
	virtual float getHeight() const = 0;
	//get num of edge
	virtual int getNumOfEdges() const = 0;
	//get my color
	const sf::Color& getColor() const { return m_color; }
	// convert to string
	virtual string toString() const;
private:
	//color
	sf::Color m_color;
};


