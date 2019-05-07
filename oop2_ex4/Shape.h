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
	Shape(float width, float height, const sf::Color& color);
	//set width
	void setWidth(float width);
	//set height
	void setHeight(float height);
	//set color
	void setColor(const sf::Color& color) { m_color = color; }
	//get width
	float getWidth() const { return m_width; }
	//get height
	float getHeight() const { return m_height; }
	//get num of edge
	virtual int getNumOfEdges() const = 0;
	//get my color
	const sf::Color& getColor() const { return m_color; }
	// convert to string
	virtual string toString() const;
private:
	//width and height
	float m_width, m_height;
	//color
	sf::Color m_color;
};


