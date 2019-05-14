#pragma once
//---- include section ------
#include <string>
#include "PlayerBase.h"

//---- using section --------
using std::string;

/*
 * UserPlayer abstract class
 */
class UserPlayer :
	public PlayerBase
{
public:
	// constructor
	UserPlayer();
	// when a player want to select a color
	virtual sf::Color selectColor();
	// check if the player is ready to play
	virtual bool isReadyToPlay() const override { return m_selected; }
	// connect to game
	virtual void connectToGame(GameScreen* gameScreen) override;
	// convert to string
	virtual string toString() const;
private:
	// my selected color
	sf::Color m_selectedColor;
	// if selected
	bool m_selected;
	// init
	void init();
};

