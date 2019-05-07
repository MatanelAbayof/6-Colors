#include "Utils.h"
#include "ColorPanel.h"

sf::Color Utils::randColor()
{
	int index = rand() % ColorPanel::COLORS.size();

	return ColorPanel::COLORS[index];
}

Utils::SquareStruct Utils::randSquareStruct()
{
	int squareStructIndex = rand() % NUM_SQUARE_STRUCTS;
	return static_cast<SquareStruct>(squareStructIndex);
}
