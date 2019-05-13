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
	Shape() = default;
	// get width
	virtual float getWidth() const = 0;
	// get height
	virtual float getHeight() const = 0;
	// get num of edge
	virtual int getNumOfEdges() const = 0;
	// convert to string
	virtual string toString() const;
};


