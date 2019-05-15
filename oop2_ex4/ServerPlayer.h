#pragma once
//---- include section ------
#include <string>
#include "NetworkPlayer.h"
#include "RequestsClientThread.h"

//---- using section --------
using std::string;

/*
 * ServerPlayer class
 */
class ServerPlayer :
	public NetworkPlayer
{
public:
	// constructor
	ServerPlayer(RequestsClientThread& clientThread);
	// when a player want to select a color
	virtual sf::Color selectColor() override;
	// check if the player is ready to play
	virtual bool isReadyToPlay() override;
	// check if the player is ready to game
	virtual bool isReadyToGame() const override;
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
	// flag that check if get color from server
	bool m_getColorFlag;
	// the client thread that communicate with server player
	RequestsClientThread& m_clientThread;
};

