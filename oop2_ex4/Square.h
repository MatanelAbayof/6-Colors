#pragma once
//---- include section ------
#include <string>
#include "Shape.h"
//---- using section --------
using std::string;

/*
 * Square class
 */
class Square :
	public Shape
{
public:
	const int NUM_OF_EDGES = 4;
	// constructor
	Square(float width, const sf::Color& color);
	//num of edges
	virtual int getNumOfEdges() const;
	// convert to string
	virtual string toString() const;
private:
	// TODO members here
};


