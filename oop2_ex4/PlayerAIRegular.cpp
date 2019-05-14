#include "PlayerAIRegular.h"


PlayerAIRegular::PlayerAIRegular()
{
}

PlayerAIRegular::~PlayerAIRegular()
{
}

sf::Color PlayerAIRegular::selectColor()
{
	// count colors of new adjacents
	std::unordered_map <sf::Color, int> colorCounter;
	for (int i = 0; i < ColorPanel::COLORS.size(); i++) {
		colorCounter[ColorPanel::COLORS[i]] = 0;
	}
	// saves checked adjacents
	std::unordered_set <GraphVertex> checkedAdj;
	// check color max occourrences
	int maxColorCounter = 0;
	// max color occorrenced
	sf::Color maxColor;

	// check all border vertices
	for (auto vertex : getBorderVertices()) {
		// check all vertex adjacents
		for (auto adj : vertex->getAdjacencyList()) {
			// check if they have different color
			if (vertex->getValue().getColor() != adj->getValue().getColor()) {
				// check if this a unchecked adjacent
				if (checkedAdj.insert(adj).second) {
					colorCounter[adj->getValue().getColor()]++;
				}
			}
		}
	}

	// take the color with the highest counter
	for (auto color : colorCounter) {
		if (color.second > maxColorCounter) {
			maxColor = color.first;
			maxColorCounter = color.second;
		}
	}

	return maxColor;
}

string PlayerAIRegular::toString() const
{
	return "PlayerAIRegular: { " + PlayerAI::toString() + " }";
}
