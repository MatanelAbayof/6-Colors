#include "PlayerBase.h"

PlayerBase::PlayerBase()
	: m_gameScreen(nullptr)
{ }

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
}

string PlayerBase::toString() const
{
	return "PlayerBase: { name=" + m_name + " }";
}