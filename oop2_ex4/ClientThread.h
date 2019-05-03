#pragma once
//---- include section ------
#include <string>
#include <mutex>  // For std::unique_lock
#include <shared_mutex>
#include <SFML/Network.hpp>
#include <thread>
#include "INetworkThread.h"

//---- using section --------
using std::string;

/*
 * ClientThread abstract class.
 * this is run in new thread
 */
class ClientThread 
	  : public INetworkThread
{
public:
	// number of times to try connect to server
	static const int NUM_CONNECT_TIMES = 20;
	// start client in new thread
	void start(const sf::IpAddress& serverIpAddress, const unsigned short port);
	// check if client is connected to server
	bool isConnectedToServer() const;
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	ClientThread();
	// build packet to send. if packet is empty so client will not send nothing
	virtual void buildPacket(sf::Packet& packet) = 0;
	// event when packet received from server
	virtual void onPacketReceived(const sf::TcpSocket& socket, sf::Packet& packet) = 0;
private:
	// socket to server
	sf::TcpSocket m_socket;
	// selector
	sf::SocketSelector m_selector;
	// mutex
	mutable std::shared_mutex m_mutex;
	// flag connected to server
	bool m_connected;
	// the client thread (run from client thread)
	void runClientThread(const sf::IpAddress& serverIpAddress, const unsigned short port);
	// try connect server (run from client thread)
	bool tryConnectServer(const sf::IpAddress& serverIpAddress, const unsigned short port);
	// set as connected to server
	void setAsConnected(bool connected);
	// exit thread (run in thread)
	void exitThread();
};

