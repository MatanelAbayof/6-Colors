#pragma once
//---- include section ------
#include <string>
#include "NetworkPlayer.h"
#include "RequestsServerThread.h"

//---- using section --------
using std::string;

/*
 * ClientPlayer class
 */
class ClientPlayer :
	public NetworkPlayer
{
public:
	// constructor
	ClientPlayer(RequestsServerThread& serverThread);
	// when a player want to select a color
	virtual sf::Color selectColor() override;
	// check if the player is ready to play
	virtual bool isReadyToPlay() override;
	// check if the player is ready to game
	virtual bool isReadyToGame() const override { return true; }
	// connect to game
	virtual void connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer) override;
	// on other player played
	virtual void onOtherPlayerPlayed(const sf::Color& selectedColor) override;
	// event on player played
	virtual void onPlayerPlayed(const sf::Color& selectedColor) override;
	// convert to string
	virtual string toString() const override;
private:
	// current color
	sf::Color m_currColor;
	// flag that check if get color from client
	bool m_getColorFlag;
	// the server thread that communicate with client player
	RequestsServerThread& m_serverThread;
};

