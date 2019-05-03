//---- include section ------
#include "INetworkThread.h"
#include "Logger.h"

// init
const sf::Int32 INetworkThread::WAIT_TIME = 10;

INetworkThread::INetworkThread()
	: m_state(State::READY), m_flagRequestExit(false)
{ }

INetworkThread::~INetworkThread()
{
	// stop thread
	stop();	
}

void INetworkThread::setRunningMode()
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_state = State::RUNNING;
	m_flagRequestExit = false;
}

void INetworkThread::requestToExit()
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_flagRequestExit = true;
}

bool INetworkThread::isRequestedToExit() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_flagRequestExit;
}

void INetworkThread::setState(State state)
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_state = state;
}

void INetworkThread::exitThread()
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_state = State::STOPPED;
	m_flagRequestExit = false;
}

string INetworkThread::stateToStr() const
{
	string str;
	switch (getState())
	{
		case State::READY: {
			str = "Ready";
		} break;
		case State::RUNNING: {
			str = "Running";
		} break;
		case State::STOPPED: {
			str = "Stopped";
		} break;
	}
	return str;
}

void INetworkThread::stop()
{
	if (getState() != State::READY) {
		requestToExit();
		// wait to thread (must do it because thread is joinable)
		m_thread.join();
	}
	setState(State::READY);
}

INetworkThread::State INetworkThread::getState() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_state;
}

string INetworkThread::toString() const
{
	return "INetworkThread: state=" + stateToStr() + ", requestToExit=" + std::to_string(isRequestedToExit());
}

