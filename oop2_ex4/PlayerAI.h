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
	virtual bool isReadyToPlay() override;
	// check if the player is ready to game
	virtual bool isReadyToGame() const override { return true; }
	// check if the player is connected to game
	virtual bool isPlayerConnected() override { return true; };
	// on other player played
	virtual void onOtherPlayerPlayed(const sf::Color& selectedColor) override;
	// event on player played
	virtual void onPlayerPlayed(const sf::Color& selectedColor) override { m_readyToPlay = false; }
	// convert to string
	virtual string toString() const override { return "Player AI: { " + PlayerBase::toString() + "}"; }
	// clean
	virtual void clean() override;
private:
	// waiting stop watch
	mutable StopWatch m_waitStopWatch;
	// ready to play
	bool m_readyToPlay;
};
