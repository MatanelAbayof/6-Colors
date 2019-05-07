#pragma once
//---- include section ------
#include <string>
#include <SFML/Graphics.hpp>

//---- using section ----------------
using std::string;

/*
 * Utilites namespace
 */
namespace Utilities {
	// numbe of square structs (in enum)
	const int NUM_SQUARE_STRUCTS = 3;
	// square structs
	enum SquareStruct {
		SQUARE, UP_DOWN_TRIG, LEFT_RIGHT_TRIG
	};
	// random color from colors in ColorPanel
	sf::Color randColor();
	//rand square struct
	SquareStruct randSquareStruct();
	// convert key code to string
	string keyCodeToString(sf::Keyboard::Key keyCode);	
}
