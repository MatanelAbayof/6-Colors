//---- include section ------
#include "ClientThread.h"
#include "NetworkException.h"

ClientThread::ClientThread()	
	: INetworkThread(), m_connected(false)
{ }

void ClientThread::start(const sf::IpAddress& serverIpAddress, const unsigned short port)
{
	// check if thread is running already
	if (getState() == State::RUNNING)
		throw NetworkException("Client thread is running");

	// init thread
	setRunningMode();

	// create new thread
	m_thread = std::thread([this, &serverIpAddress, &port] {
		this->runClientThread(serverIpAddress, port);
	});
}

bool ClientThread::isConnectedToServer() const
{
	std::shared_lock<std::shared_mutex> lock(m_mutex);
	return m_connected;
}

string ClientThread::toString() const
{
	return "ClientThread: { state=" + INetworkThread::toString() + " }";
}

void ClientThread::runClientThread(const sf::IpAddress& serverIpAddress, const unsigned short port)
{
	m_selector.clear();

	// connect to server
	if (!tryConnectServer(serverIpAddress, port)) {
		exitThread();
		return;
	}

	setAsConnected(true);

	// add socket to selector
	m_selector.add(m_socket);

	while (!isRequestedToExit()) {
		// wait to receive data
		if (m_selector.wait(sf::milliseconds(WAIT_TIME))) {
			if (m_selector.isReady(m_socket)) {
				// read message
				sf::Packet packet;
				if (m_socket.receive(packet) != sf::Socket::Done) {
					break; // exit
				}

				// call receive event
				onPacketReceived(m_socket, packet);
			}
		}

		// build packet
		sf::Packet packet;
		buildPacket(packet);

		// check if packet is not empty
		if (packet.getDataSize() > 0) {
			// send message to server
			if (m_socket.send(packet) != sf::Socket::Done) {
				//LOG("Client: send failed");
				break; // exit
			}
		}
	}

	// exit from thread
	exitThread();
}

bool ClientThread::tryConnectServer(const sf::IpAddress & serverIpAddress, const unsigned short port)
{	
	for (int i = 0; i < NUM_CONNECT_TIMES; i++) {
		sf::Socket::Status status = m_socket.connect(serverIpAddress, port);
		if (status == sf::Socket::Done) {
			return true;
		}
		// wait a little bit
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return false;
}

void ClientThread::setAsConnected(bool connected)
{
	std::unique_lock<std::shared_mutex> lock(m_mutex);
	m_connected = connected;
}

void ClientThread::exitThread()
{
	INetworkThread::exitThread();
	setAsConnected(false);
}
