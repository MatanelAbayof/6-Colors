#pragma once
//---- include section ------
#include "View.h"
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
	void setColor(const sf::Color& color) { m_polygonShape.setFillColor(color); }
	// get color
	const sf::Color& getColor() const { return m_polygonShape.getFillColor(); }
	// draw in window
	virtual void draw() override;
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
private:
	// polygon shape
	sf::ConvexShape m_polygonShape;
	// relative points of polygon
	std::vector<sf::Vector2f> m_relPoints;
	// update polygon shape
	void updatePolygonShape();
	// check if relative point is legal
	bool isLegalRelPoint(const sf::Vector2f& relPoint) const { return (isRelativeNum(relPoint.x) && isRelativeNum(relPoint.y)); }
	// check if is number in [0, 1]
	bool isRelativeNum(float num) const { return ((num >= 0.f) && (num <= 1.f)); }
};

