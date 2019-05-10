#include "Board.h"
#include "Triangle.h"
#include "Square.h"
#include "Utilities.h"

Board::Board(sf::RenderWindow& window)
	: RelativeLayout<PolygonView>(window)
{ }

void Board::setBoardSize(const sf::Vector2i& boardSize)
{
	// check board size
	if (boardSize.x <= 0 || boardSize.y <= 0 || boardSize.y%2 != 0)
		throw std::length_error("Board size {x=" + std::to_string(boardSize.x) + ", y=" + 
			                    std::to_string(boardSize.y) + "} must be with possitive numbers and y is even number");

	clear();
	m_boardSize = boardSize;
}

void Board::clear()
{
	m_polygonsGraph.clear();
	removeAllViews();
}

void Board::addView(const std::shared_ptr<PolygonView>& polygonView, const sf::FloatRect& relativeBounds)
{
	RelativeLayout<PolygonView>::addView(polygonView, relativeBounds);
	m_polygonsGraph.addVertex(polygonView);
}

string Board::toString() const
{
	return "Board: { graph=" + m_polygonsGraph.toString() + ", boardSize={ rows=" + std::to_string(m_boardSize.x) + ", " +
		std::to_string(m_boardSize.y) + ", " + RelativeLayout<PolygonView>::toString() + " }";
}

void Board::randomizeBoard(const sf::Vector2i& boardSize)                                          // TODO must set adjs!!!!
{
	// set board size
	setBoardSize(boardSize);

	// check if board is set
	if (m_boardSize.x == 0 || m_boardSize.y == 0)
		throw std::length_error("Board size isn't set");

	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	// add top triangles (first row)
	randomizeBoardEdgeLine(true);

	// add shapes exclude last row
	for (int rowNum = 1; rowNum < m_boardSize.y; ++rowNum) {

		if (rowNum%2 == 1) {
			// add Triangle in left side
			std::unique_ptr<PolygonShape> rightTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::RIGHT);
			std::shared_ptr<PolygonView> rightTrigView = std::make_shared<PolygonView>(getWindow(), std::move(rightTrig));
			addView(rightTrigView, sf::FloatRect(0.f, float(rowNum-1)*shapeHeight, shapeWidth / 2.f, 2.f*shapeHeight));
		}
		
		// add shapes in line
		for (int colNum = (rowNum % 2 == 0) ? 0 : 1; colNum < m_boardSize.x; ++colNum) {
			randSquareStructShape(rowNum, colNum);
		}

		// add Triangle in right side
		if (rowNum % 2 == 1) {
			// add Triangle in left side
			std::unique_ptr<PolygonShape> leftTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::LEFT);
			std::shared_ptr<PolygonView> leftTrigView = std::make_shared<PolygonView>(getWindow(), std::move(leftTrig));
			addView(leftTrigView, sf::FloatRect((float(m_boardSize.x) - 0.5f)*shapeWidth, float(rowNum - 1)*shapeHeight, shapeWidth / 2.f, 2.f*shapeHeight));
		}
		
	}

	// add trigs in bottom (last row)
	randomizeBoardEdgeLine(false);
}

void Board::randomizeBoardEdgeLine(bool isFirstLine)
{
	Triangle::PointingSide trigSide;
	float trigsY;

	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	if (isFirstLine) {
		trigSide = Triangle::PointingSide::DOWN;
		trigsY = 0.f;
	}
	else {
		trigSide = Triangle::PointingSide::UP;
		trigsY = (m_boardSize.y-1.f)*shapeHeight;
	}

	for (int colNum = 0; colNum < m_boardSize.x; ++colNum) {
		std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(Utilities::randColor(), trigSide);
		std::shared_ptr<PolygonView> downTrigView = std::make_shared<PolygonView>(getWindow(), std::move(downTrig));
		sf::FloatRect downTrigBounds(float(colNum) * shapeWidth, trigsY, shapeWidth, shapeHeight);
		addView(downTrigView, downTrigBounds);
	}
}

void Board::randSquareStructShape(int rowNum, int colNum)
{
	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	// random shapes in current square struct
	Utilities::SquareStruct squareStruct = Utilities::randSquareStruct();
	switch (squareStruct)
	{
	case Utilities::SquareStruct::SQUARE: {
		std::unique_ptr<PolygonShape> square = std::make_unique<Square>(Utilities::randColor());
		std::shared_ptr<PolygonView> squareView = std::make_shared<PolygonView>(getWindow(), std::move(square));
		sf::FloatRect squareBounds;
		if (rowNum % 2 == 0)
			squareBounds.left = float(colNum)*shapeWidth;
		else
			squareBounds.left = float(2 * colNum - 1)*(shapeWidth / 2.f);
		squareBounds.top = float(rowNum - 1)*shapeHeight;
		squareBounds.width = shapeWidth;
		squareBounds.height = 2.f * shapeHeight;
		addView(squareView, squareBounds);
	} break;
	case Utilities::SquareStruct::UP_DOWN_TRIG: {

		std::unique_ptr<PolygonShape> upTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::UP);
		std::shared_ptr<PolygonView> upTrigView = std::make_shared<PolygonView>(getWindow(), std::move(upTrig));
		std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::DOWN);
		std::shared_ptr<PolygonView> downTrigView = std::make_shared<PolygonView>(getWindow(), std::move(downTrig));
		sf::FloatRect upTrigBounds, downTrigBounds;
		if (rowNum % 2 == 0) {
			downTrigBounds.left = upTrigBounds.left = float(colNum)*shapeWidth;
		}
		else
			downTrigBounds.left = upTrigBounds.left = (float(colNum) - 0.5f)*shapeWidth;
		upTrigBounds.top = float(rowNum - 1) / (m_boardSize.y);
		downTrigBounds.top = upTrigBounds.top + shapeHeight;
		upTrigBounds.width = downTrigBounds.width = shapeWidth;
		upTrigBounds.height = downTrigBounds.height = shapeHeight;
		addView(upTrigView, upTrigBounds);
		addView(downTrigView, downTrigBounds);
	} break;
	case Utilities::SquareStruct::LEFT_RIGHT_TRIG: {
		std::unique_ptr<PolygonShape> leftTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::LEFT);
		std::shared_ptr<PolygonView> leftTrigView = std::make_shared<PolygonView>(getWindow(), std::move(leftTrig));
		std::unique_ptr<PolygonShape> rightTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::RIGHT);
		std::shared_ptr<PolygonView> rightTrigView = std::make_shared<PolygonView>(getWindow(), std::move(rightTrig));
		sf::FloatRect leftTrigBounds, rightTrigBounds;
		if (rowNum % 2 == 0) {
			leftTrigBounds.left = float(colNum)*shapeWidth;
			rightTrigBounds.left = leftTrigBounds.left + shapeWidth/2.f;
		}
		else {
			leftTrigBounds.left = (float(colNum) - 0.5f)*shapeWidth;
			rightTrigBounds.left = leftTrigBounds.left + shapeWidth/2.f;
		}
		leftTrigBounds.top = rightTrigBounds.top = float(rowNum - 1)*shapeHeight;
		leftTrigBounds.width = rightTrigBounds.width = shapeWidth/2.f;
		leftTrigBounds.height = rightTrigBounds.height = 2.f*shapeHeight;
		addView(leftTrigView, leftTrigBounds);
		addView(rightTrigView, rightTrigBounds);
	} break;
	}
}
