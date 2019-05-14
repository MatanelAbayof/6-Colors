#include "PlayerBase.h"

PlayerBase::PlayerBase()
	: m_gameScreen(nullptr)
{ }

void PlayerBase::connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer)
{
	m_gameScreen = gameScreen;
	m_rivalPlayer = rivalPlayer;
}

GameScreen* PlayerBase::getGameScreen()
{
	if (m_gameScreen == nullptr)
		throw std::logic_error("Cannot find game screen");
	return m_gameScreen;
}

void PlayerBase::setStartVertex(GraphVertex vertex)
{
	m_playerVertices.insert(vertex);
	m_borderVertices.insert(vertex);
	m_lastColor = vertex->getValue().getColor();
}

std::vector<sf::Color> PlayerBase::getForbiddenColors() const
{
	std::vector<sf::Color> forbiddenColors;
	forbiddenColors.push_back(getLastColor());
	forbiddenColors.push_back(m_rivalPlayer->getLastColor());
	return forbiddenColors;
}

string PlayerBase::toString() const
{
	return "PlayerBase: { name=" + m_name + " }";
}