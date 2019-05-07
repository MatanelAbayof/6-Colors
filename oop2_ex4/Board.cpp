#include "Board.h"

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
