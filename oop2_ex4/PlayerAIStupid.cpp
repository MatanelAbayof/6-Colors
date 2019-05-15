#include "PlayerAIStupid.h"

sf::Color PlayerAIStupid::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");
	// select color
	sf::Color selectedColor = Utilities::randColor(getForbiddenColors());
	// update last color
	setLastColor(selectedColor);
	// call events
	onPlayerPlayed(selectedColor);
	getRivalPlayer()->onOtherPlayerPlayed(selectedColor);
	return selectedColor;
}

string PlayerAIStupid::toString() const
{
	return "PlayerAIStupid: { " + PlayerAI::toString() + " }";
}
