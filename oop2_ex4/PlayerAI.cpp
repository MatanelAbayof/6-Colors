#include "PlayerAI.h"

PlayerAI::PlayerAI()
	: m_readyToPlay(false)
{
	setName("Computer");
}

bool PlayerAI::isReadyToPlay()
{
	m_waitStopWatch.checkStopWatch();
	return m_readyToPlay;
}

void PlayerAI::onOtherPlayerPlayed(const sf::Color& selectedColor)
{
	int waitTime = 200 + rand()%1000;
	m_waitStopWatch.start(waitTime, [this]() {
		m_readyToPlay = true;
	});
}

void PlayerAI::clean()
{
	PlayerBase::clean();
	m_readyToPlay = false;
}
