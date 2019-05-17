#pragma once
//---- include section ------
#include <string>
#include "Graph.h"
#include "PolygonView.h"
#include <SFML/Graphics/Color.hpp>
#include "PlayerBase.h"

//---- using section --------
using std::string;

/*
 * ColoringAlgorithem class
 */
class ColoringAlgorithm
{
public:
	// set of vertices
	using VertexSet = std::unordered_set<PlayerBase::GraphVertex>;
	// constructor
	ColoringAlgorithm() = default;
	// color the graph
	void colorGraph(VertexSet& playerVertex, VertexSet& borderVertex, const sf::Color& color);
	// convert to string
	virtual string toString() const;
private:
	// add adjacent vertices
	void addAdj(VertexSet& playerVertex, VertexSet& borderVertex, PlayerBase::GraphVertex vertex);
};

