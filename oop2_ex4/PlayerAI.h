#pragma once
//---- include section ------
#include <string>
#include "PlayerBase.h"

//---- using section --------
using std::string;

/*
 * PlayerAI abstract class
 */
class PlayerAI :
	public PlayerBase
{
public:
	PlayerAI() = default;
	virtual bool isReadyToPlay() const override { return true; }
	// convert to string
	virtual string toString() const override { return "Player AI: { " + PlayerBase::toString() + "}"; }
};
