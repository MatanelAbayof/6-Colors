#include "PlayerAI.h"

PlayerAI::PlayerAI()
	: m_readyToPlay(false)                // TODO m_readyToPlay = false      when played!!!!
{
	setName("Computer");
}

bool PlayerAI::isReadyToPlay() const
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
