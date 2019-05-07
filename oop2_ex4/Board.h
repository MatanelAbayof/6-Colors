#pragma once
//---- include section ------
#include <string>
#include <memory>
#include "RelativeLayout.h"
#include "Graph.h"
#include "PolygonView.h"
//---- using section --------
using std::string;

/*
 * Board class
 */
class Board :
	public GUI::RelativeLayout<PolygonView>
{
public:
	// constructor
	explicit Board(sf::RenderWindow& window, const sf::Vector2i& boardSize = { 0,0 });
	// set board size
	void setBoardSize(const sf::Vector2i& boardSize);
	// randomize board
	void randomizeBoard();
	// clear board
	void clear();
	// get board size
	const sf::Vector2i& getboardSize() const { return m_boardSize; }
	// add polygon view
	virtual void addView(const std::shared_ptr<PolygonView>& polygonView, const sf::FloatRect& relativeBounds) override;
	// get polygons graph
	Graph<PolygonView>& getPolygonsGraph() { return m_polygonsGraph; }
	// convert to string
	virtual string toString() const override;
private:
	// board size (number of shapes)
	sf::Vector2i m_boardSize;
	// polygons
	Graph<PolygonView> m_polygonsGraph;
};

