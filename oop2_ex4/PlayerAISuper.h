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
 * PlayerAISuper class
 */

class PlayerAISuper:
	public PlayerAI
{
public:
	// constructor
	PlayerAISuper();
	// destructor
	~PlayerAISuper();
	// select color
	virtual sf::Color selectColor() override;
	// convert to string
	virtual string toString() const;
private:
	int countAdj(GraphVertex vertex, std::unordered_set <GraphVertex>& checkedAdj);
};


