#pragma once
//---- include section ------
#include <string>
#include <functional>
#include <vector>
#include "Cell.h"

//---- using section --------
using std::string;
using GUI::Cell;

/*
 * generic matrix class
 */
template <class T>
class Matrix
{
public:
	// iterator of matrix
	class iterator {
		public:
			// constructor
			explicit iterator(Matrix<T>& matrix, const Cell& cell = { 0, 0 } );
			// check if iterator is in end of matrix
			bool isEnd() const;
			// get data
			T& operator*();
			T* operator->();
			// go to next cell
			iterator& operator++(); // prefix
			iterator operator++(int); // postfix
			// get cell
			const Cell& getCell() const { return m_cell; }
			// overload operators
			bool operator==(const iterator& other) const { return m_cell == other.m_cell; }
			bool operator!=(const iterator& other) const { return m_cell != other.m_cell; }
		private:
			// cell of iterator
			Cell m_cell;
			// matrix
			Matrix<T>& m_matrix;
			// set cell
			void setCell(const Cell& cell) { m_cell = cell; }
	};

	// constructor
	explicit Matrix(int numOfRows = 0, int numOfCols = 0);
	// set size
	void resize(int numOfRows, int numOfCols);
	// get number of rowss
	int getNumOfRows() const { return m_numOfRows; }
	// get number of columns
	int getNumOfCols() const { return m_numOfCols; }
	// clear
	void clear() { m_data.clear(); }
	// overload ==,!= operators
	bool operator==(const Matrix<T>& otherMatrix) const { return m_data == otherMatrix.m_data; }
	bool operator!=(const Matrix<T>& otherMatrix) const { return m_data != otherMatrix.m_data; }
	// get cell data (for non-const access)
	T& operator[](const Cell& cell);
	// get cell data (for const access)
	const T& operator[](const Cell& cell) const;
	// for each all cells
    void forEach(std::function<void(const Cell&, T&)> onGetCellData);
	// get iterator to begin of matrix
	iterator begin() { return iterator(*this); }
	// get iterator to end of matrix
	iterator end() { return iterator(*this, getEndCell()); }
	// check if cell exists
	bool isCellExists(const Cell& cell) const { return ((cell.getRowNum() < m_numOfRows) && (cell.getColNum() < m_numOfCols)); }
	// convert to string
	virtual string toString() const { return "Matrix: { rows=" + std::to_string(m_numOfRows) + ", cols=" + std::to_string(m_numOfCols) +" }"; }
private:
	// matrix data
	std::vector<std::vector<T>> m_data;
	// matrix dimensions
	int m_numOfRows, m_numOfCols;
	// check legal dimensions
	bool isLegalSize(int numOfRows, int numOfCols) const { return ((numOfRows >= 0) && (numOfCols >= 0)); }
	// get one cell after last cell
	Cell getEndCell() { return Cell(getNumOfRows(), 0); };
};

template<class T>
Matrix<T>::Matrix(int numOfRows, int numOfCols)
{
	resize(numOfRows, numOfCols);
}

template<class T>
void Matrix<T>::resize(int numOfRows, int numOfCols)
{
	if (!isLegalSize(numOfRows, numOfCols))
		throw std::out_of_range("Ilegal size of matrix: rows=" + std::to_string(numOfRows) + ", cols=" + std::to_string(numOfCols));
	m_numOfRows = numOfRows;
	m_numOfCols = numOfCols;
	// delete last matrix
	m_data.clear();
	// set matrix size
	m_data.resize(numOfRows);
	for (int rowNum = 0; rowNum < m_numOfRows; rowNum++) {
		m_data[rowNum].resize(numOfCols);
	}
}

template<class T>
T& Matrix<T>::operator[](const Cell& cell)
{
	if (!isCellExists(cell))
		throw std::out_of_range("The cell: " + cell.toString() + " doesn't exists in matrix");
	return m_data[cell.getRowNum()][cell.getColNum()];
}

template<class T>
const T& Matrix<T>::operator[](const Cell& cell) const
{
	if (!isCellExists(cell))
		throw std::out_of_range("The cell: " + cell.toString() + " doesn't exists in matrix");
	return m_data[cell.getRowNum()][cell.getColNum()];
}


template<class T>
void Matrix<T>::forEach(std::function<void(const Cell&, T&)> onGetCellData)
{
	for (auto it = begin(); it != end(); ++it) {
		onGetCellData(it.getCell(), *it);
	}
}

template<class T>
Matrix<T>::iterator::iterator(Matrix<T>& matrix, const Cell& cell) : m_matrix(matrix)
{ 
	setCell(cell);
}
template<class T>
typename Matrix<T>::iterator& Matrix<T>::iterator::operator++()
{
	// increment cell by one
	if (m_cell.getColNum() + 1 == m_matrix.getNumOfCols())
		m_cell.setCell(m_cell.getRowNum() + 1, 0);
	else
		m_cell.setColNum(m_cell.getColNum() + 1);
	return *this;
}

template<class T>
typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int)
{
	iterator tempIt = *this;
	++(*this);
	return tempIt;
}

template<class T>
bool Matrix<T>::iterator::isEnd() const
{
	return !m_matrix.isCellExists(m_cell);
}

template<class T>
T& Matrix<T>::iterator::operator*()
{
	if (isEnd())
		throw std::out_of_range("Iterator of matrix at " + m_cell.toString() + " is out of range ");
	return m_matrix[m_cell];
}

template<class T>
T* Matrix<T>::iterator::operator->()
{
	return &operator*();
}
