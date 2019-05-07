#pragma once
//---- include section ------
#include <string>
#include "PolygonShape.h"

//---- using section --------
using std::string;

/*
 * Triangle class
 */

class Triangle :
	public PolygonShape
{
public:
	enum PointingSide { UP, DOWN, LEFT, RIGHT };
	// constructor
	Triangle(const sf::Color& color = sf::Color::Transparent, PointingSide pointingSide = PointingSide::UP);
	//get width
	virtual float getWidth();
	//get height
	virtual float getHeight();
	//get num of edge
	virtual int getNumOfEdges();
	// convert to string
	virtual string toString() const;
private:
	// the side the tringle points to
	PointingSide m_pointingSide;
	// init
	void init();
};

