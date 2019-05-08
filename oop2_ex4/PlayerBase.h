#pragma once
//---- include section ------
#include <string>
#include <unordered_set>
#include <SFML/Graphics/Color.hpp>
#include "Shape.h"

//---- using section --------
using std::string;

/*
 * PlayerBase abstract class
 */
class PlayerBase
{
public:
	// when a player wnt to select a color
	virtual sf::Color selectColor() = 0;
	// get player name
	const string& getName() const;
	// set player name
	void setName(const string& name);
	// check if the player is ready to play
	virtual bool isReadyToPlay() = 0;
	// convert to string
	virtual string toString() const;
private:
	// constructor
	PlayerBase();
	// destructor
	~PlayerBase();
	string m_name;
	std::unordered_set<Shape*> m_filldsShapes;
};

