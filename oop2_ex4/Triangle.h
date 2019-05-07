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
	// pointing side
	enum PointingSide { UP, DOWN, LEFT, RIGHT };
	// constructor
	explicit Triangle(const sf::Color& color = sf::Color::Transparent, PointingSide pointingSide = PointingSide::UP);
	// get width
	virtual float getWidth() const override;
	// get height
	virtual float getHeight() const override;
	// get num of edge
	virtual int getNumOfEdges() const override;
	// convert to string
	virtual string toString() const override;
private:
	// the side the tringle points to
	PointingSide m_pointingSide;
	// init
	void init();
};

