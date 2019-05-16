#include "ServerPlayer.h"

ServerPlayer::ServerPlayer(RequestsClientThread& clientThread)
	: m_clientThread(clientThread), m_getColorFlag(false)
{ }

sf::Color ServerPlayer::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");

	setLastColor(m_currColor);
	// call events
	onPlayerPlayed(m_currColor);
	getRivalPlayer()->onOtherPlayerPlayed(m_currColor);
	m_getColorFlag = false;
	return m_currColor;
}

bool ServerPlayer::isReadyToPlay()
{
	if(m_getColorFlag)
		return true;

	std::unique_ptr<int> colorInt = m_clientThread.getReceiveRequests().tryPop();
	if (colorInt != nullptr) {
		m_currColor = sf::Color(*colorInt);
		m_getColorFlag = true;
		return true;
	}

	return false;
}

bool ServerPlayer::isReadyToGame() const
{
	std::unique_ptr<int> seed = m_clientThread.getReceiveRequests().tryPop();
	if (seed != nullptr) {
		srand(*seed);
		return true;
	}
	return false;
}

void ServerPlayer::connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer)
{
	NetworkPlayer::connectToGame(gameScreen, rivalPlayer);
}

void ServerPlayer::onOtherPlayerPlayed(const sf::Color& selectedColor)
{
	m_clientThread.getSendRequests().push(selectedColor.toInteger());
}

void ServerPlayer::onPlayerPlayed(const sf::Color& selectedColor)
{ }

bool ServerPlayer::isPlayerConnected()
{
	return m_clientThread.isConnectedToServer();
}

string ServerPlayer::toString() const
{
	return "ServerPlayer: { " + NetworkPlayer::toString() + " }";
}
