#include "ClientPlayer.h"
#include "Logger.h"

ClientPlayer::ClientPlayer(RequestsServerThread& serverThread)
	: m_serverThread(serverThread), m_getColorFlag(false)
{ }

sf::Color ClientPlayer::selectColor()
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

bool ClientPlayer::isReadyToPlay()
{
	if (m_getColorFlag)
		return true;

	std::unique_ptr<int> colorInt = m_serverThread.getReceiveRequests().tryPop();
	if (colorInt != nullptr) {
		m_currColor = sf::Color(*colorInt);
		m_getColorFlag = true;
		return true;
	}

	return false;
}

void ClientPlayer::connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer)
{
	NetworkPlayer::connectToGame(gameScreen, rivalPlayer);

	int seed = rand();
	LOG("seed: " + std::to_string(seed));
	srand(seed);
	m_serverThread.getSendRequests().push(seed);
}

void ClientPlayer::onOtherPlayerPlayed(const sf::Color& selectedColor)
{
	m_serverThread.getSendRequests().push(selectedColor.toInteger());
}

void ClientPlayer::onPlayerPlayed(const sf::Color& selectedColor)
{ }

string ClientPlayer::toString() const
{
	return "ClientPlayer: { " + NetworkPlayer::toString() + " }";
}
