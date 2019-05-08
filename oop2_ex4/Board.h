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
	explicit Board(sf::RenderWindow& window);
	// randomize board
	void randomizeBoard(const sf::Vector2i& boardSize);
	// clear board
	void clear();
	// get board size
	const sf::Vector2i& getBoardSize() const { return m_boardSize; }
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
	// randomize board edge line
	void randomizeBoardEdgeLine(bool isFirstLine);
	// randomize square struct shape
	void randSquareStructShape(int rowNum, int colNum);
	// set board size
	void setBoardSize(const sf::Vector2i& boardSize);
};

