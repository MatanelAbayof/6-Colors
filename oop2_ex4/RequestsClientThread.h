#pragma once
//---- include section ------
#include "ClientThread.h"
#include "RequestsQueue.h"

//---- using section --------
using std::string;

/*
 * RequestsClientThread class
 */
class RequestsClientThread 
	 : public ClientThread
{
public:
	// constructor
	explicit RequestsClientThread(RequestsQueue<string>& sendRequests,
		                 RequestsQueue<string>& receiveRequests);
	// convert to string
	virtual string toString() const override;
protected:
	// events
	virtual void buildPacket(sf::Packet& packet) override;
	virtual void onPacketReceived(const sf::TcpSocket& socket, sf::Packet& packet) override;
private:
	// request queue
	RequestsQueue<string>& m_sendRequests,& m_receiveRequests;
};

