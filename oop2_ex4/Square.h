#pragma once
//---- include section ------
#include <string>
#include "PolygonShape.h"
//---- using section --------
using std::string;

/*
 * Square class
 */
class Square :
	public PolygonShape
{
public:
	// number of edges
	static const int NUM_OF_EDGES = 4;
	// constructor
	Square();
	// get width
	virtual float getWidth() const { return getHeight(); }
	// get height
	virtual float getHeight() const { return (getPoint(2).y - getPoint(0).y); }
	// number of edges
	virtual int getNumOfEdges() const { return NUM_OF_EDGES; }
	// convert to string
	virtual string toString() const override;
private:
	// init 
	void init();
};


