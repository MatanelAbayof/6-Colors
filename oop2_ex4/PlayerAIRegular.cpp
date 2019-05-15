#include "PlayerAIRegular.h"


PlayerAIRegular::PlayerAIRegular()
{
}

PlayerAIRegular::~PlayerAIRegular()
{
}

sf::Color PlayerAIRegular::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");

	// count colors occurrences of new adjacents
	std::unordered_map <int, int> colorCounter;
	for (int i = 0; i < ColorPanel::COLORS.size(); i++) {
		// get the number that represnt the color
		colorCounter[ColorPanel::COLORS[i].toInteger()] = 0;
	}
	// saves checked adjacents
	std::unordered_set <GraphVertex> checkedAdj;
	// check color max occourrences
	int maxColorCounter = 0;
	// max color occorrenced (represented as an int)
	int maxColor;
	sf::Color selectedColor;

	// check all border vertices
	for (auto vertex : getBorderVertices()) {
		// check all vertex adjacents
		for (auto adj : vertex->getAdjacencyList()) {
			// check if they have different color
			// TODO forbidden colors
			if (vertex->getValue().getColor() != adj->getValue().getColor()) {
				// check if this a unchecked adjacent
				if (checkedAdj.insert(adj).second) {
					colorCounter[adj->getValue().getColor().toInteger()]++;
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

	// convert int to color
	selectedColor = sf::Color(maxColor);
	setLastColor(selectedColor);
	onPlayerPlayed(selectedColor);
	getRivalPlayer()->onOtherPlayerPlayed(selectedColor);
	return selectedColor;
}

string PlayerAIRegular::toString() const
{
	return "PlayerAIRegular: { " + PlayerAI::toString() + " }";
}
