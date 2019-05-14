#include "ColoringAlgorithm.h"



/*
ColoringAlgorithm::ColoringAlgorithm(Graph<PolygonView>& polygonsGraph)
	:m_polygonsGraph(polygonsGraph)
{
}

ColoringAlgorithm::~ColoringAlgorithm()
{
}

void ColoringAlgorithm::colorGraph(VertexSet& playerVertex, VertexSet& borderVertex, sf::Color color)
{
	// color all players vertixes
	for (auto vertex : playerVertex) {
		vertex->getValue().setColor(color);
	}

	// add new vertices
	for (auto vertex : borderVertex) {
		addAdj(playerVertex, borderVertex, vertex);
	}
}

void ColoringAlgorithm::addAdj(VertexSet& playerVertex, VertexSet& borderVertex, PlayerBase::GraphVertex vertex)
{
	// check if the vertix still nedds to be in border vetices
	bool throwFromBorder = true;
	for (auto adj : vertex->getAdjacencyList()) {
		// check if it's the same color
		if (adj->getValue().getColor() == vertex->getValue().getColor()) {
			// check if it's a new vertex
			if (playerVertex.insert(adj).second) {
				// add to border vertices
				borderVertex.insert(adj);
				// check new vertix adjacents (recursion)
				addAdj(playerVertex, borderVertex, adj);
			}
		}
		// vertix is still relevant to border
		else {
			throwFromBorder = false;
		}
	}
	if (throwFromBorder) {
		borderVertex.erase(vertex);
	}
}

string ColoringAlgorithm::toString() const
{
	return "Coloring Algorithm";
}*/
