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
	virtual bool isReadyToPlay() const override { return m_selected; }
	// connect to game
	virtual void connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer) override;
	// on other player played
	virtual void onOtherPlayerPlayed(const sf::Color& selectedColor) override;
	// event on player played
	virtual void onPlayerPlayed(const sf::Color& selectedColor) override { m_selected = false; }
	// set start vertex
	virtual void setStartVertex(GraphVertex vertex) override;
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

