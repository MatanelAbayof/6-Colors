//---- include section ------
#include "ServerThread.h"
#include "Logger.h"
#include "NetworkException.h"

ServerThread::ServerThread()
	: INetworkThread(), m_blockNewConnections(true), m_numOfClients(0)
{ }

ServerThread::~ServerThread()
{
	clear();
}

void ServerThread::start(const unsigned short port)
{
	// check if thread is running already
	if (getState() == State::RUNNING)
		throw NetworkException("Server thread is running");

	// init thread
	setRunningMode();

	// reset block connections
	setBlockConnections(false);

	// create new thread
	m_thread = std::thread([this, &port] {
		this->runServerThread(port);
	});
}

void ServerThread::stop()
{
	INetworkThread::stop();
	clear();
}

void ServerThread::setBlockConnections(bool block)
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_blockNewConnections = block;
}

bool ServerThread::isBlockNewConnections() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_blockNewConnections;
}

int ServerThread::getNumOfClients() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_numOfClients;
}

string ServerThread::toString() const
{
	return "ServerClient: { numOfClients=" + std::to_string(m_clients.size()) + ", " + INetworkThread::toString() + " }";
}

void ServerThread::runServerThread(const unsigned short port)
{
	// bind the listener to a port
	if (m_listener.listen(port) != sf::Socket::Done) {
		exitThread();
		return;
	}

	// add listener to selector
	m_selector.add(m_listener);

	while (!isRequestedToExit()) {
		// wait to receive data or new client
		if (m_selector.wait(sf::milliseconds(WAIT_TIME))) {
			// test the listener
			if (m_selector.isReady(m_listener)) {
				// check if is not blocking new connections
				if (!isBlockNewConnections()) {
					std::unique_ptr<sf::TcpSocket> client = std::make_unique<sf::TcpSocket>();
					if (m_listener.accept(*client) == sf::Socket::Done) {
						sf::TcpSocket* pClient = client.get();
						// add the new client to the clients list
						m_clients.push_back(std::move(client));
						// add to selector
						m_selector.add(*pClient);
						// add 1 client
						setNumOfClients(static_cast<int>(m_clients.size()));
						// call event
						onClientJoined(*pClient);
					}
					else {
						exitThread();
						return;
					}
				}
			} else {
				// The listener socket is not ready, test all other sockets (the clients)
				for (ClientList::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
					sf::TcpSocket& client = **it;
					if (m_selector.isReady(client)) {
						// The client has sent some data, we can receive it
						sf::Packet packet;
						if (client.receive(packet) == sf::Socket::Done) {
							// call event
							onPacketReceived(client, packet);
						}
						else {
							exitThread();
							return;
						}
					}
				}
			}
		}

		// build packet
		sf::Packet packet;
		buildPacket(packet);

		// check if packet is not empty
		if (packet.getDataSize() > 0) {
			// send data to clients
			for (ClientList::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
				sf::TcpSocket& client = **it;

				// send message to client
				if (client.send(packet) != sf::Socket::Done) {
					exitThread();
					return;
				}
			}
		}		
	}

	// exit thread
	exitThread();
}

void ServerThread::clear()
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_blockNewConnections = true;
	m_clients.clear();
	m_listener.close();
	m_selector.clear();
}

void ServerThread::setNumOfClients(int numOfClients)
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_numOfClients = numOfClients;
}


