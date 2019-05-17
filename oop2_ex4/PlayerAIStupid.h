
#pragma once
//---- include section ------
#include <string>
#include "PlayerAI.h"
#include "Utilities.h" // for colors

//---- using section --------
using std::string;

/*
 * PlayerAIStupid class
 */
class PlayerAIStupid :
	public PlayerAI
{
public:
	// constructor
	PlayerAIStupid() = default;
	// select color
	virtual sf::Color selectColor() override;
	// convert to string
	virtual string toString() const override;
};

