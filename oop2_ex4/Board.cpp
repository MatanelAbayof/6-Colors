#include "Board.h"
#include "Triangle.h"
#include "Square.h"
#include "Utils.h"

Board::Board(sf::RenderWindow& window, const sf::Vector2i& boardSize)
	: RelativeLayout<PolygonView>(window)
{
	setBoardSize(boardSize);
}

void Board::setBoardSize(const sf::Vector2i& boardSize)
{
	clear();
	m_boardSize = boardSize;
}

void Board::randomizeBoard()
{
	for (int colNum = 0; colNum < m_boardSize.x; ++colNum) {
		std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(sf::Color::Blue, Triangle::PointingSide::DOWN);
		std::shared_ptr<PolygonView> downTrigView = std::make_shared<PolygonView>(getWindow(), std::move(downTrig));
		sf::FloatRect downTrigBounds;
		downTrigBounds.left = float(colNum) / m_boardSize.x;
		downTrigBounds.top = 0.f;
		downTrigBounds.width = 1.f / m_boardSize.x;
		downTrigBounds.height = 1.f / m_boardSize.y;
		addView(downTrigView, downTrigBounds);
	}

	for (int rowNum = 1; rowNum < m_boardSize.y; ++rowNum) {

		// TODO add Trig right

		int i;
		if (rowNum % 2 == 0) {
			i = 0;
		}
		else {
			i = 1;
		}
		
		for (; i < m_boardSize.x; ++i) {

			Utils::SquareStruct squareStruct = Utils::randSquareStruct();
			switch (squareStruct)
			{
				case Utils::SquareStruct::SQUARE: {
					std::unique_ptr<PolygonShape> shape = std::make_unique<Square>(Utils::randColor()); 
					std::shared_ptr<PolygonView> shapeView = std::make_shared<PolygonView>(getWindow(), std::move(shape));
					sf::FloatRect downTrigBounds;
					if (rowNum % 2 == 0)
						downTrigBounds.left = float(2 * i) / (2.f*m_boardSize.x);
					else
						downTrigBounds.left = float(2 * i - 1) / (2.f*m_boardSize.x);
					downTrigBounds.top = float(rowNum - 1) / (m_boardSize.y);
					downTrigBounds.width = 1.f / m_boardSize.x;
					downTrigBounds.height = 2.f / m_boardSize.y;
					addView(shapeView, downTrigBounds);
				} break;
				case Utils::SquareStruct::UP_DOWN_TRIG: {

					std::unique_ptr<PolygonShape> upTrig = std::make_unique<Triangle>(Utils::randColor(), Triangle::PointingSide::UP);
					std::shared_ptr<PolygonView> upTrigView = std::make_shared<PolygonView>(getWindow(), std::move(upTrig));
					std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(Utils::randColor(), Triangle::PointingSide::DOWN);
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
				case Utils::SquareStruct::LEFT_RIGHT_TRIG: {
					std::unique_ptr<PolygonShape> leftTrig = std::make_unique<Triangle>(Utils::randColor(), Triangle::PointingSide::LEFT);
					std::shared_ptr<PolygonView> leftTrigView = std::make_shared<PolygonView>(getWindow(), std::move(leftTrig));
					std::unique_ptr<PolygonShape> rightTrig = std::make_unique<Triangle>(Utils::randColor(), Triangle::PointingSide::RIGHT);
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

		// TODO add Trig left

		
	}
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
