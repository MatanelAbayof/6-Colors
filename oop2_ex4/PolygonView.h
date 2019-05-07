#pragma once
//---- include section ------
#include "View.h"
#include "Polygon.h"
#include <string>
//---- using section --------
using std::string;

/*
 * PolygonView class
 */
class PolygonView :
	public GUI::View
{
public:
	// constructor
	PolygonView(sf::RenderWindow& window, const sf::Color& color = sf::Color::Transparent);
	// add relative point to polygon
	void addPoint(const sf::Vector2f& relPoint);
	// set color
	void setColor(const sf::Color& color);
	// get color
	const sf::Color& getColor() const { return m_polygon.getColor(); }
	// draw in window
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
private:
	// polygon drawable shape
	sf::ConvexShape m_polygonDrawable;
	// polygon shape
	Polygon m_polygon;
	// update polygon shape
	void updatePolygonShape();	
};

