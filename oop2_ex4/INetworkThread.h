#pragma once
//---- include section ------
#include <string>
#include <mutex>  // For std::unique_lock
#include <shared_mutex>
#include <SFML/Network.hpp>

//---- using section --------
using std::string;

/*
 * INetworkThread interface
 */
class INetworkThread
{
public:
	// defualt port of network
	static const unsigned short DEFUAT_PORT = 30123;
	// wait time in millis
	static const sf::Int32 WAIT_TIME;
	// state of thread
	enum State {
		RUNNING, STOPPED, READY
	};
	// stop thread
	virtual void stop();
	// get state
	State getState() const;
	// convert to string
	virtual string toString() const;
protected:
	// client thread
	std::thread m_thread;
	// mutex
	mutable std::shared_mutex m_mutex;
	// constructor
	INetworkThread();
	// destructor
	virtual ~INetworkThread();
	// set running mode
	void setRunningMode();
	// check if is requested to exit
	bool isRequestedToExit() const;
	// set state
	void setState(State state);
	// exit thread (run in thread)
	void exitThread();
private:
	// state
	State m_state;
	// request to exit
	bool m_flagRequestExit;
	// request to exit
	void requestToExit();
	// convert state to string
	string stateToStr() const;
	// disable copy class
	INetworkThread& operator=(const INetworkThread&) = delete;
	INetworkThread(const INetworkThread&) = delete;
};

