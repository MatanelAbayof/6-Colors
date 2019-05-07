#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>

/*
* Utils namespace
*/
namespace Utils {
	const int NUM_SQUARE_STRUCTS = 3;
	enum SquareStruct {
		SQUARE, UP_DOWN_TRIG, LEFT_RIGHT_TRIG 
	};
	//rand color
	sf::Color randColor();
	//rand square struct
	SquareStruct randSquareStruct();
}