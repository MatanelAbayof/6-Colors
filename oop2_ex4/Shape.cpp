#include "Shape.h"

string Shape::toString() const
{
	return "Shape: { Width = " + std::to_string(getWidth()) + ", Height: " + std::to_string(getHeight()) + ", Num of edges: " + std::to_string(getNumOfEdges()) + " }";
}
