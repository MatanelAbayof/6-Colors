#include "PlayerAIStupid.h"

sf::Color PlayerAIStupid::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");
	sf::Color selectedColor = Utilities::randColor(getForbiddenColors());
	setLastColor(selectedColor);
	onPlayerPlayed(selectedColor);
	getRivalPlayer()->onOtherPlayerPlayed(selectedColor);
	return selectedColor;
}

string PlayerAIStupid::toString() const
{
	return "PlayerAIStupid: { " + PlayerAI::toString() + " }";
}
