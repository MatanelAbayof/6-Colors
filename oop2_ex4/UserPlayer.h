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
	virtual sf::Color selectColor() override;
	// check if the player is ready to play
	virtual bool isReadyToPlay() override { return m_selected; }
	// check if the player is ready to game
	virtual bool isReadyToGame() const override { return true; }
	// connect to game
	virtual void connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer) override;
	// on other player played
	virtual void onOtherPlayerPlayed(const sf::Color& selectedColor) override;
	// event on player played
	virtual void onPlayerPlayed(const sf::Color& selectedColor) override;
	// check if the player is connected to game
	virtual bool isPlayerConnected() override { return true; };
	// set start vertex
	virtual void setStartVertex(GraphVertex vertex) override;
	// clean
	virtual void clean() override;
	// convert to string
	virtual string toString() const override;
private:
	// flag that check if selected
	bool m_selected;
	// init
	void init();
	// update forbidden colors in color panel
	void updateForbiddenColors();
};

