#pragma once
//---- include section ------
#include <string>
#include "PlayerAI.h"
#include "ColorPanel.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

//---- using section --------
using std::string;

/*
 * PlayerAIRegular class
 */

class PlayerAIRegular :
	public PlayerAI
{
public:
	// constructor
	PlayerAIRegular();
	// destructor
	~PlayerAIRegular();
	// select color
	virtual sf::Color selectColor() override;
	// convert to string
	virtual string toString() const;
private:
	// TODO members here
};


