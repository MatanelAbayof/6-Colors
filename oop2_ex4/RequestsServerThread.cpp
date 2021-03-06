//---- include section ------------
#include "RequestsServerThread.h"
#include "Logger.h"

RequestsServerThread::RequestsServerThread(RequestsQueue<int>& sendRequests,
	                                       RequestsQueue<int>& receiveRequests)
	: ServerThread(), m_sendRequests(sendRequests), m_receiveRequests(receiveRequests)
{ }

string RequestsServerThread::toString() const
{
	return "RequestsServerThread: { numSendRequests=" + std::to_string(m_sendRequests.size()) + ", numReceivedRequests=" +
			std::to_string(m_receiveRequests.size()) + ", " + ServerThread::toString() + " }";
}

void RequestsServerThread::onClientJoined(const sf::TcpSocket& clientSocket)
{
	// Do nothing...
}

void RequestsServerThread::buildPacket(sf::Packet& packet)
{
	// try get packet from send requests
	std::unique_ptr<int> request = m_sendRequests.tryPop();
	if (request != nullptr) {
		packet << *request;
	}
}

void RequestsServerThread::onPacketReceived(const sf::TcpSocket& socket, sf::Packet& packet)
{
	// parse packet
	int message;
	packet >> message;

	// add new request
	m_receiveRequests.push(message);
}
