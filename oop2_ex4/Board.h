#pragma once
//---- include section ------
#include <string>
#include <memory>
#include "View.h"
#include "Graph.h"
#include "PolygonView.h"
//---- using section --------
using std::string;

/*
 * Board class
 */
class Board :
	public GUI::View
{
public:
	// constructor
	Board(sf::RenderWindow& window, const sf::Vector2i& boardSize = { 0,0 });
	// draw in window
	virtual void draw() override;
	// set board size
	void setBoardSize(const sf::Vector2i& boardSize);
	// get board size
	const sf::Vector2i& getboardSize() const { return m_boardSize; }
	// get polygons graph
	Graph<PolygonView>& getPolygons();
	// convert to string
	virtual string toString() const override;
protected:
	// update components
	virtual void updateComponents() override;
private:
	// board size (number of shapes)
	sf::Vector2i m_boardSize;
	// polygons
	Graph<PolygonView> m_polygons;
};

