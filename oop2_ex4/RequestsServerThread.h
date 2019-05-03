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
	explicit RequestsServerThread(RequestsQueue<string>& sendRequests,
		                 RequestsQueue<string>& receiveRequests);
	// convert to string
	virtual string toString() const override;
protected:
	// events
	virtual void onClientJoined(const sf::TcpSocket& clientSocket) override;
	virtual void buildPacket(sf::Packet& packet) override;
	virtual void onPacketReceived(const sf::TcpSocket& socket, sf::Packet& packet) override;
private:
	// request queue
	RequestsQueue<string>& m_sendRequests, &m_receiveRequests;
};

