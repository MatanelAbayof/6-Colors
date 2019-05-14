#include "PlayerAIStupid.h"

sf::Color PlayerAIStupid::selectColor()
{
	return Utilities::randColor();
}

string PlayerAIStupid::toString() const
{
	return "PlayerAIStupid: { " + PlayerAI::toString() + " }";
}
