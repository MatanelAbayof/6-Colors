#include "Board.h"
#include "Triangle.h"
#include "Square.h"
#include "Utilities.h"

Board::Board(sf::RenderWindow& window, const sf::Vector2i& boardSize)
	: RelativeLayout<PolygonView>(window)
{
	setBoardSize(boardSize);
}

void Board::setBoardSize(const sf::Vector2i& boardSize)
{
	// check board size
	if (boardSize.x < 0 || boardSize.y < 0)
		throw std::length_error("Board size {x=" + std::to_string(boardSize.x) + ", y=" + std::to_string(boardSize.y) + "} must be a natural numbers");

	clear();
	m_boardSize = boardSize;
}

void Board::randomizeBoard()                                          // TODO must set adjs!!!!
{
	// check if board is set
	if (m_boardSize.x == 0 || m_boardSize.y == 0)
		throw std::length_error("Board size isn't set");

	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	// add top triangles (first row)
	for (int colNum = 0; colNum < m_boardSize.x; ++colNum) {
		std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::DOWN);
		std::shared_ptr<PolygonView> downTrigView = std::make_shared<PolygonView>(getWindow(), std::move(downTrig));
		sf::FloatRect downTrigBounds(float(colNum) * shapeWidth, 0.f, shapeWidth, shapeHeight);
		addView(downTrigView, downTrigBounds);
	}

	// add shapes exclude last row
	for (int rowNum = 1; rowNum < m_boardSize.y; ++rowNum) {


		// TODO add Trigangle in left side

	
		for (int i = (rowNum % 2 == 0) ? 0 : 1; i < m_boardSize.x; ++i) {
			// random shapes in current square struct
			Utilities::SquareStruct squareStruct = Utilities::randSquareStruct();
			switch (squareStruct)
			{
				case Utilities::SquareStruct::SQUARE: {
					std::unique_ptr<PolygonShape> square = std::make_unique<Square>(Utilities::randColor());
					std::shared_ptr<PolygonView> squareView = std::make_shared<PolygonView>(getWindow(), std::move(square));
					sf::FloatRect squareBounds;
					if (rowNum % 2 == 0)
						squareBounds.left = float(i)*shapeWidth;
					else
						squareBounds.left = float(2 * i - 1) / (2.f*m_boardSize.x);
					squareBounds.top = float(rowNum - 1) / (m_boardSize.y);
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
						downTrigBounds.left = upTrigBounds.left = float(2 * i) / (2.f*m_boardSize.x);
					}
					else
						downTrigBounds.left = upTrigBounds.left = float(2 * i - 1) / (2.f*m_boardSize.x);
					upTrigBounds.top = float(rowNum - 1) / (m_boardSize.y);
					downTrigBounds.top = upTrigBounds.top + 1.f / m_boardSize.y;
					upTrigBounds.width = downTrigBounds.width = 1.f / m_boardSize.x;
					upTrigBounds.height = downTrigBounds.height = 1.f / m_boardSize.y;
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
						leftTrigBounds.left = float(2 * i) / (2.f*m_boardSize.x);
						rightTrigBounds.left = leftTrigBounds.left + (1.f / (2.f*m_boardSize.x));
					}
					else {
						leftTrigBounds.left = float(2 * i - 1) / (2.f*m_boardSize.x);
						rightTrigBounds.left = leftTrigBounds.left + (1.f / (2.f*m_boardSize.x));
					}
					leftTrigBounds.top = rightTrigBounds.top = float(rowNum - 1) / (m_boardSize.y);
					leftTrigBounds.width = rightTrigBounds.width = 1.f / (2.f*m_boardSize.x);
					leftTrigBounds.height = rightTrigBounds.height = 2.f / m_boardSize.y;
					addView(leftTrigView, leftTrigBounds);
					addView(rightTrigView, rightTrigBounds);
				} break;
			}			
		}

		// TODO add Trigangle in right side

		
	}

	// TODO add trigs in bottom (last row)
}

void Board::clear()
{
	removeAllViews();
	m_polygonsGraph.clear();
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
