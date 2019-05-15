#pragma once
//---- include section ------
#include <string>
#include "PlayerBase.h"

//---- using section --------
using std::string;

/*
 * NetworkPlayer class
 */
class NetworkPlayer :
	public PlayerBase
{
public:
	// constructor
	NetworkPlayer();
	// convert to string
	virtual string toString() const override { return "NetworkPlayer: { " + PlayerBase::toString() + " }"; }
};

