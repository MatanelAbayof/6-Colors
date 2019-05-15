//---- include section ----------
#include "RequestsClientThread.h"
#include "Logger.h"

RequestsClientThread::RequestsClientThread(RequestsQueue<int>& sendRequests,
	                                       RequestsQueue<int>& receiveRequests)
	: ClientThread(), m_sendRequests(sendRequests), m_receiveRequests(receiveRequests)
{ }

string RequestsClientThread::toString() const
{
	return "RequestsClientThread: { numSendRequests=" + std::to_string(m_sendRequests.size()) + ", numReceivedRequests=" +
			std::to_string(m_receiveRequests.size()) + ", " + ClientThread::toString() + " }";
}

void RequestsClientThread::buildPacket(sf::Packet& packet)
{
	// try get packet from send requests
	std::unique_ptr<int> request = m_sendRequests.tryPop();
	if (request != nullptr) {
		packet << *request;	
	}
}

void RequestsClientThread::onPacketReceived(const sf::TcpSocket& socket, sf::Packet& packet)
{
	// parse packet
	int message;
	packet >> message;

	// add new request
	m_receiveRequests.push(message);
}
