#pragma once
//---- include section ------
#include <string>
#include "PlayerBase.h"
#include "StopWatch.h"

//---- using section --------
using std::string;

/*
 * PlayerAI abstract class
 */
class PlayerAI :
	public PlayerBase
{
public:
	// constructor
	PlayerAI();
	// check if the player is ready to play
	virtual bool isReadyToPlay() const;
	// on other player played
	virtual void onOtherPlayerPlayed(const sf::Color& selectedColor);
	// event on player played
	virtual void onPlayerPlayed(const sf::Color& selectedColor) { m_readyToPlay = false; }
	// convert to string
	virtual string toString() const override { return "Player AI: { " + PlayerBase::toString() + "}"; }
private:
	// waiting stop watch
	mutable StopWatch m_waitStopWatch;
	// ready to play
	bool m_readyToPlay;
};
