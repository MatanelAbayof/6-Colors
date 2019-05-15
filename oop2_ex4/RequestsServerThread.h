#pragma once
//---- include section ------
#include "ServerThread.h"
#include "RequestsQueue.h"

//---- using section --------
using std::string;

/*
 * RequestsServerThread class
 */
class RequestsServerThread
	: public ServerThread
{
public:
	// constructor
	explicit RequestsServerThread(RequestsQueue<int>& sendRequests,
		                 RequestsQueue<int>& receiveRequests);
	// get send requests
	RequestsQueue<int>& getSendRequests() { return m_sendRequests; }
	// get receive requests
	RequestsQueue<int>& getReceiveRequests() { return m_receiveRequests; }
	// convert to string
	virtual string toString() const override;
protected:
	// events
	virtual void onClientJoined(const sf::TcpSocket& clientSocket) override;
	virtual void buildPacket(sf::Packet& packet) override;
	virtual void onPacketReceived(const sf::TcpSocket& socket, sf::Packet& packet) override;
private:
	// request queue
	RequestsQueue<int>& m_sendRequests, &m_receiveRequests;
};

