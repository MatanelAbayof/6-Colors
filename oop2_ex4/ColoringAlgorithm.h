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
	using VertexSet = std::unordered_set<PlayerBase::GraphVertex>;
	// constructor
	ColoringAlgorithm();
	// destructor
	~ColoringAlgorithm();
	// color the graph
	void colorGraph(VertexSet& playerVertex, VertexSet& borderVertex, sf::Color color);
	// convert to string
	virtual string toString() const;
private:
	//Graph<PolygonView> m_polygonsGraph;
	// add adjacent vertixes
	void addAdj(VertexSet& playerVertex, VertexSet& borderVertex, PlayerBase::GraphVertex vertex);
};

