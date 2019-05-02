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

	// convert key code to string
	string keyCodeToString(sf::Keyboard::Key keyCode);	
}
