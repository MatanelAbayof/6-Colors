#pragma once
//---- include section ------
#include <string>
#include <mutex>  // For std::unique_lock
#include <shared_mutex>
#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include "INetworkThread.h"

//---- using section --------
using std::string;

/*
 * ServerThread abstract class.
 * this is run in new thread
 */
class ServerThread : public INetworkThread
{
public:
	// start server in new thread
	void start(const unsigned short port);
	// stop thread
	virtual void stop() override;
	// set block new connections
	void setBlockConnections(bool block);
	// check if server block new connections
	bool isBlockNewConnections() const;
	// get number of clients
	/*size_t getNumOfClients() const; */						// TODO make this function safe!!!!!!!!!!!!!!!!!!
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	ServerThread();
	// destructor
	virtual ~ServerThread();
	// event when new client joined to server
	virtual void onClientJoined(const sf::TcpSocket& clientSocket) = 0;
	// build packet to send to all clients. if packet is empty so server will not send nothing
	virtual void buildPacket(sf::Packet& packet) = 0;
	// event when packet received from server
	virtual void onPacketReceived(const sf::TcpSocket& clientSocket, sf::Packet& packet) = 0;
private:
	// selector
	sf::SocketSelector m_selector;
	// listener
	sf::TcpListener m_listener;
	// list of clients
	std::list<sf::TcpSocket*> m_clients;
	// flag for block new connections
	bool m_blockNewConnections;
	// run server thread
	void runServerThread(const unsigned short port);
	// clear
	void clear();
};

