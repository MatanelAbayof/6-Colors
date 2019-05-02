#pragma once
//---- include section ------
#include <string>

//---- using section --------
using std::string;

namespace GUI {
/*
 * Cell class
 */
class Cell
{
public:
	// default row number and column number of cell
	static const int DEFAULT_ROW_NUM = 0, DEFAULT_COL_NUM = 0;
	// constructor
	Cell(int rowNum = DEFAULT_ROW_NUM, int colNum = DEFAULT_COL_NUM);
	//get num of row
	int getRowNum() const { return m_rowNum; }
	//get num of column
	int getColNum() const { return m_colNum; }
    //set new cell
	void setCell(int rowNum, int colNum);
	// set row number
	void setRowNum(int rowNum);
	// set column number
	void setColNum(int colNum);
	// check if cell is above the other
	bool isAboveThen(const Cell& otherCell) const { return (m_rowNum == otherCell.m_rowNum - 1 && m_colNum == otherCell.m_colNum); }
	// check if cell is under the other
	bool isUnderThen(const Cell& otherCell) const { return (m_rowNum == otherCell.m_rowNum + 1 && m_colNum == otherCell.m_colNum); }
	// check if cell is left to the other
	bool isLeftTo(const Cell& otherCell) const { return (m_rowNum == otherCell.m_rowNum && m_colNum == otherCell.m_colNum - 1); }
	// check if cell is right to the other
	bool isRightTo(const Cell& otherCell) const { return (m_rowNum == otherCell.m_rowNum && m_colNum == otherCell.m_colNum + 1); }
	// check if the cell is valid
	static bool isValidCell(int rowNum, int colNum);
	// convert to string
	virtual string toString() const;
	// overloading compare operator
	bool operator==(const Cell& anotherCell) const { return (getRowNum() == anotherCell.getRowNum()) && (getColNum() == anotherCell.getColNum()); }
	// overloading compare operator
	bool operator!=(const Cell& anotherCell) const { return !(*this == anotherCell); }
private:
	// number of row
	int m_rowNum;
	// number of column
	int m_colNum;
};
}