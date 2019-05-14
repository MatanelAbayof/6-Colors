#pragma once
//---- include section ------
#include <string>
#include <memory>
#include "RelativeLayout.h"
#include "Graph.h"
#include "PolygonView.h"
#include "Matrix.h"
#include "Utilities.h"
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
	// square struct info
	struct SquareStructInfo {
		// constructor
		SquareStructInfo() : m_squareStruct(Utilities::SquareStruct::SQUARE) {}
		// square struct type
		Utilities::SquareStruct m_squareStruct;
		// list of vertices
		std::vector<Graph<PolygonView>::Vertex*> m_vertices;
	};
	// board size (number of shapes)
	sf::Vector2i m_boardSize;
	// polygons
	Graph<PolygonView> m_polygonsGraph;
	// randomize board edge line
	void randomizeBoardEdgeLine(Matrix<SquareStructInfo>& shapesMatrix, bool isFirstLine);
	// randomize square struct shape
	void randSquareStructShape(Matrix<SquareStructInfo>& shapesMatrix, const Cell& cell);
	// set adjs at graph
	void setAdjs(Matrix<SquareStructInfo>& shapesMatrix);
	// set board size
	void setBoardSize(const sf::Vector2i& boardSize);
};

