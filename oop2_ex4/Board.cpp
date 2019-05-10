#include "Board.h"
#include "Triangle.h"
#include "Square.h"
#include "Utilities.h"
#include "Matrix.h"

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

	// random results in matrix
	Matrix<SquareStructInfo> shapesMatrix(boardSize.y+1, boardSize.x+1);

	// check if board is set
	if (m_boardSize.x == 0 || m_boardSize.y == 0)
		throw std::length_error("Board size isn't set");

	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	// add top triangles (first row)
	randomizeBoardEdgeLine(shapesMatrix, true);

	// add shapes exclude last row
	for (int rowNum = 1; rowNum < m_boardSize.y; ++rowNum) {

		if (rowNum%2 == 1) {
			// add Triangle in left side
			std::unique_ptr<PolygonShape> rightTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::RIGHT);
			std::shared_ptr<PolygonView> rightTrigView = std::make_shared<PolygonView>(getWindow(), std::move(rightTrig));
			// add to board
			addView(rightTrigView, sf::FloatRect(0.f, float(rowNum-1)*shapeHeight, shapeWidth / 2.f, 2.f*shapeHeight));
			shapesMatrix[Cell(rowNum, 0)].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
		}
		
		// add shapes in line
		for (int colNum = (rowNum % 2 == 0) ? 0 : 1; colNum < m_boardSize.x; ++colNum) {
			Cell cell(rowNum, colNum);
			randSquareStructShape(shapesMatrix, cell);
		}

		// add Triangle in right side
		if (rowNum % 2 == 1) {
			// add Triangle in left side
			std::unique_ptr<PolygonShape> leftTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::LEFT);
			std::shared_ptr<PolygonView> leftTrigView = std::make_shared<PolygonView>(getWindow(), std::move(leftTrig));
			addView(leftTrigView, sf::FloatRect((float(m_boardSize.x) - 0.5f)*shapeWidth, float(rowNum - 1)*shapeHeight, shapeWidth / 2.f, 2.f*shapeHeight));
			shapesMatrix[Cell(rowNum, shapesMatrix.getNumOfCols()-1)].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
		}
		
	}

	// add trigs in bottom (last row)
	randomizeBoardEdgeLine(shapesMatrix, false);

	setAdjs(shapesMatrix);
}

void Board::randomizeBoardEdgeLine(Matrix<SquareStructInfo>& shapesMatrix, bool isFirstLine)
{
	Triangle::PointingSide trigSide;
	int rowNum;
	float trigsY;

	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	if (isFirstLine) {
		rowNum = 0;
		trigSide = Triangle::PointingSide::DOWN;
		trigsY = 0.f;
	}
	else { // last line
		rowNum = shapesMatrix.getNumOfRows() - 1;
		trigSide = Triangle::PointingSide::UP;
		trigsY = (m_boardSize.y-1.f)*shapeHeight;
	}

	for (int colNum = 0; colNum < m_boardSize.x; ++colNum) {
		Cell cell(rowNum, colNum);
		std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(Utilities::randColor(), trigSide);
		std::shared_ptr<PolygonView> downTrigView = std::make_shared<PolygonView>(getWindow(), std::move(downTrig));
		sf::FloatRect downTrigBounds(float(colNum) * shapeWidth, trigsY, shapeWidth, shapeHeight);
		addView(downTrigView, downTrigBounds);
		shapesMatrix[cell].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
	}
}

void Board::randSquareStructShape(Matrix<SquareStructInfo>& shapesMatrix, const Cell& cell)
{
	// the shape size
	float shapeWidth = 1.f / float(m_boardSize.x);
	float shapeHeight = 1.f / float(m_boardSize.y);

	// random shapes in current square struct
	Utilities::SquareStruct squareStruct = Utilities::randSquareStruct();
	shapesMatrix[cell].m_squareStruct = squareStruct;
	switch (squareStruct)
	{
		case Utilities::SquareStruct::SQUARE: {
			std::unique_ptr<PolygonShape> square = std::make_unique<Square>(Utilities::randColor());
			std::shared_ptr<PolygonView> squareView = std::make_shared<PolygonView>(getWindow(), std::move(square));
			sf::FloatRect squareBounds;
			if (cell.getRowNum() % 2 == 0)
				squareBounds.left = float(cell.getColNum())*shapeWidth;
			else
				squareBounds.left = float(2 * cell.getColNum() - 1)*(shapeWidth / 2.f);
			squareBounds.top = float(cell.getRowNum() - 1)*shapeHeight;
			squareBounds.width = shapeWidth;
			squareBounds.height = 2.f * shapeHeight;
			addView(squareView, squareBounds);
			// add square vertex to matrix
			shapesMatrix[cell].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
		} break;
		case Utilities::SquareStruct::UP_DOWN_TRIG: {

			std::unique_ptr<PolygonShape> upTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::UP);
			std::shared_ptr<PolygonView> upTrigView = std::make_shared<PolygonView>(getWindow(), std::move(upTrig));
			std::unique_ptr<PolygonShape> downTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::DOWN);
			std::shared_ptr<PolygonView> downTrigView = std::make_shared<PolygonView>(getWindow(), std::move(downTrig));
			sf::FloatRect upTrigBounds, downTrigBounds;
			if (cell.getRowNum() % 2 == 0) {
				downTrigBounds.left = upTrigBounds.left = float(cell.getColNum())*shapeWidth;
			}
			else
				downTrigBounds.left = upTrigBounds.left = (float(cell.getColNum()) - 0.5f)*shapeWidth;
			upTrigBounds.top = float(cell.getRowNum() - 1) / (m_boardSize.y);
			downTrigBounds.top = upTrigBounds.top + shapeHeight;
			upTrigBounds.width = downTrigBounds.width = shapeWidth;
			upTrigBounds.height = downTrigBounds.height = shapeHeight;
			addView(upTrigView, upTrigBounds);
			// add up triangle vertex to matrix
			shapesMatrix[cell].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
			addView(downTrigView, downTrigBounds);
			// add down triangle vertex to matrix
			shapesMatrix[cell].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
		} break;
		case Utilities::SquareStruct::LEFT_RIGHT_TRIG: {
			std::unique_ptr<PolygonShape> leftTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::LEFT);
			std::shared_ptr<PolygonView> leftTrigView = std::make_shared<PolygonView>(getWindow(), std::move(leftTrig));
			std::unique_ptr<PolygonShape> rightTrig = std::make_unique<Triangle>(Utilities::randColor(), Triangle::PointingSide::RIGHT);
			std::shared_ptr<PolygonView> rightTrigView = std::make_shared<PolygonView>(getWindow(), std::move(rightTrig));
			sf::FloatRect leftTrigBounds, rightTrigBounds;
			if (cell.getRowNum() % 2 == 0) {
				leftTrigBounds.left = float(cell.getColNum())*shapeWidth;
				rightTrigBounds.left = leftTrigBounds.left + shapeWidth/2.f;
			}
			else {
				leftTrigBounds.left = (float(cell.getColNum()) - 0.5f)*shapeWidth;
				rightTrigBounds.left = leftTrigBounds.left + shapeWidth/2.f;
			}
			leftTrigBounds.top = rightTrigBounds.top = float(cell.getRowNum() - 1)*shapeHeight;
			leftTrigBounds.width = rightTrigBounds.width = shapeWidth/2.f;
			leftTrigBounds.height = rightTrigBounds.height = 2.f*shapeHeight;
			addView(leftTrigView, leftTrigBounds);
			// add left triangle vertex to matrix
			shapesMatrix[cell].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
			addView(rightTrigView, rightTrigBounds);
			// add right triangle vertex to matrix
			shapesMatrix[cell].m_vertices.push_back(m_polygonsGraph.getVertex(m_polygonsGraph.getNumOfVertices() - 1));
		} break;
	}
}

void Board::setAdjs(Matrix<SquareStructInfo>& shapesMatrix)
{
	for (int rowNum = 1; rowNum < shapesMatrix.getNumOfRows()-1; ++rowNum) {
		for (int colNum = 1; colNum < shapesMatrix.getNumOfCols()-2; ++colNum) {
			Cell cell(rowNum, colNum);
			SquareStructInfo& ssi = shapesMatrix[cell];

			// add adjs
			switch (ssi.m_squareStruct)
			{
				case Utilities::SquareStruct::SQUARE: { // TODO need add 4 adjs here
					SquareStructInfo* adjSsi = &shapesMatrix[Cell(rowNum - 1, colNum - 1)];

					switch (adjSsi->m_squareStruct) {
						case Utilities::SquareStruct::SQUARE: {
							ssi.m_vertices[0]->addAdjacent(adjSsi->m_vertices[0]);
						} break;
						case Utilities::SquareStruct::UP_DOWN_TRIG: {
							// TODO
						} break;
						case Utilities::SquareStruct::LEFT_RIGHT_TRIG: {
							// TODO
						} break;
					}					
				} break;
				case Utilities::SquareStruct::UP_DOWN_TRIG: {
					// TODO
				} break;
				case Utilities::SquareStruct::LEFT_RIGHT_TRIG: {
					// TODO
				} break;
			}
		}
	}
}
