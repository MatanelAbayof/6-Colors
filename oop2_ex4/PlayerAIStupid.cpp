#include "PlayerAIStupid.h"

sf::Color PlayerAIStupid::selectColor()
{
	sf::Color selectedColor = Utilities::randColor();
	setLastColor(selectedColor);
	getRivalPlayer()->onOtherPlayerPlayed(selectedColor);
	return selectedColor;
}

string PlayerAIStupid::toString() const
{
	return "PlayerAIStupid: { " + PlayerAI::toString() + " }";
}
