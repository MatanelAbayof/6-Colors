/*
 * main for tests
 */
//#define MATANEL_TESTS
#ifdef MATANEL_TESTS

 //-------------- libs -------------------------
#pragma region Libs
// for SFML library
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib, "sfml-network-d.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#else
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib, "sfml-network.lib" )
#pragma comment ( lib, "sfml-audio-d.lib" )
#endif
#pragma endregion

//-------------- include section ---------------
#pragma region Includes
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp> // JSON library
#include <iostream>
#include <thread>
#include <Windows.h>
#include <sstream>
#include "View.h"
#include "VerticalLayout.h"
#include "EditText.h"
#include "ImageButton.h"
#include "ErrorDialog.h"
#include "Logger.h"
#include "RequestsClientThread.h"
#include "RequestsServerThread.h"
#include "Graph.h"
#include "PolygonView.h"
#include "PolygonShape.h"
#include "Square.h"
#pragma endregion

//-------------- using section -----------------
#pragma region Usings
using namespace GUI;
#pragma endregion

//-------------- declare functions -------------
#pragma region Declarations
void testPolygon();
void testGraph();
sf::Color randColor();
void testGUI();
void testClientAndServerNetwork();
void testClientNetwork(const unsigned short port);
void testServerNetwork(const unsigned short port);
void testCleanScreen();
#pragma endregion

// -------------- globals & constants --------------------

//--------------  main ------------------------
int main()
{
    std::cout << "Hello Matanel World!\n";
	// initialize random seed
	srand(unsigned (time(NULL)));

	try
	{
		testPolygon();
		//testGraph();
		//testClientAndServerNetwork();
		//testGUI();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
	}
}

void testPolygon() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "GUI");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);


	for (int i = 0; i < 3; i++) {
		// create polygon
		std::unique_ptr<PolygonShape> poly = std::make_unique<Square>(sf::Color::Yellow);
		std::shared_ptr<PolygonView> polygonView = std::make_shared<PolygonView>(window, std::move(poly));		
		polygonView->addClickListener([polygonView](View& view) {
			polygonView->setColor(randColor());
		});
		mainLayout.addView(polygonView);
	}
	
	
	//PolygonShape p1;
	//

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

void testGraph() {
	// create graph
	Graph<string> graph;

	// add vertices
	for (int i = 0; i < 10; i++) {
		auto value = std::make_shared<string>("vertex_" + std::to_string(i));
		graph.addVertex(value);
	}

	// add adjacents
	for (int i = 0; i < graph.getNumOfVertices()-2; i++) {
		auto vertex = graph.getVertex(i);
		vertex->addAdjacent(graph.getVertex(i + 1));
		vertex->addAdjacent(graph.getVertex(i + 1)); // graph ignore duplicate adjs
		vertex->addAdjacent(graph.getVertex(i + 2));
	}

	// print graph
	std::cout << graph.toString() << std::endl;
	for (int i = 0; i < graph.getNumOfVertices(); i++) {
		std::cout << "V[" << i << "] = " << graph.getVertex(i)->getValue() << std::endl;
		std::cout << graph.getVertex(i)->toString() << std::endl;
	}
}

void testClientAndServerNetwork() {
	// create port
	const unsigned short port = 30123 + rand()%100;

	// create server theard
	std::thread server(testServerNetwork, port);
	server.detach(); // make thread as unjoinable

	// create clients threads
	std::vector<std::unique_ptr<std::thread>> clients;
	int numOfClients = 3;
	for (int i = 0; i < numOfClients; i++) {
		std::unique_ptr<std::thread> clientTheard = std::make_unique<std::thread>(testClientNetwork, port);
		clientTheard->detach();
	}

	// wait
	std::this_thread::sleep_for(std::chrono::seconds(2000));
}

void testClientNetwork(const unsigned short port) {
	// get thread id
	std::ostringstream clientTheardIdStream;
	clientTheardIdStream << GetCurrentThreadId();
	string clientTheardId = clientTheardIdStream.str();

	string clientPreText = "client " + clientTheardId;

	// server IP address
	string serverIpAddressStr = sf::IpAddress::getLocalAddress().toString();
	sf::IpAddress serverIpAddress(serverIpAddressStr);


	LOG(clientPreText + ": connecting to ip = " + serverIpAddressStr + " at port " + std::to_string(port) + "...");

	// create requests queues
	RequestsQueue<string> sendRequests, receiveRequests;

	// create client thread
	RequestsClientThread clientThread(sendRequests, receiveRequests);

	// connect to server
	clientThread.start(serverIpAddress, port);

	// wait to server
	while (!clientThread.isConnectedToServer()) {

		// TODO do work...

		// check if thread exit
		if (clientThread.getState() == RequestsClientThread::State::STOPPED) {
			LOG(clientPreText + ": exit");
			return; // exit
		}

		// breathe...
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}


	LOG(clientPreText + ": connected to server!");

	// run main thread - "the game"
	while (true) {

		// check if disconnected
		if (!clientThread.isConnectedToServer()) {
			LOG(clientPreText + ": disconnected");
			return; // exit
		}

		// check if have request from server
		std::unique_ptr<string> serverRequest = receiveRequests.tryPop();
		if (serverRequest != nullptr) {
			// print request
			LOG(clientPreText + ": get '" + *serverRequest + "'");
		}

		// send data to server
		string messageToServer = "Message from " + clientTheardId;
		sendRequests.push(messageToServer);
		LOG(clientPreText + ": sent '" + messageToServer + "'");

		// wait
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void testServerNetwork(const unsigned short port) {
	// say hello
	LOG("server: listen to port = " + std::to_string(port));

	// create requests queues
	RequestsQueue<string> sendRequests, receiveRequests;

	// create server
	RequestsServerThread serverThread(sendRequests, receiveRequests);
	serverThread.start(port);

	// wait for 1 client
	while (serverThread.getNumOfClients() == 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	LOG("server: i have 1 client");

	// run main thread - "the game"
	while (true) {

		// block connetions
		//serverThread.setBlockConnections(true);

		// check if have request from client
		std::unique_ptr<string> clientRequest = receiveRequests.tryPop();
		if (clientRequest != nullptr) {
			// print request
			LOG("Server: get '" + *clientRequest + "'");
		}

		// send data to clients
		string messageToClients = "Message from server";
		sendRequests.push(messageToClients);
		LOG("server: sent '" + messageToClients + "'");

		// breathe...
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void testGUI() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "GUI");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(3);
	//mainLayout.setBorder(Border(sf::Color::Blue, 5));
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.addKeyDownListener(View::KeyDownHandler::Listener([&mainLayout](sf::Keyboard::Key& keyCode) {
		switch (keyCode)
		{
		case sf::Keyboard::Key::A: {
			mainLayout.getBorder().setSize(mainLayout.getBorder().getSize() + 1);
		} break;
		case sf::Keyboard::Key::S: {
			mainLayout.getBorder().setSize(mainLayout.getBorder().getSize() - 1);
		} break;
		case sf::Keyboard::Key::D: {
			mainLayout.getBorder().setColor(randColor());
		} break;
		case sf::Keyboard::Key::F: {
			std::cout << mainLayout.toString() << std::endl;
		} break;
		}
	}));

	// add edit text
	std::shared_ptr<EditText> et = std::make_shared<EditText>(window, "Text");
	et->setTextColor(sf::Color::Black);
	//	et.setBorder(Border(sf::Color::Magenta, 1));
	et->setTextHAlignment(TextView::TextHAlignment::LEFT);
	et->startRecordText();
	mainLayout.addView(et);

	mainLayout.addKeyDownListener([&mainLayout, &window, &et](auto key) {
		if (key == sf::Keyboard::Key::A) {
			mainLayout.addView(std::make_shared<TextView>(window, et->getText()));
		}
	});
	for (int i = 0; i < 3; i++) {
		// add image view
		std::shared_ptr<ImageButton> ib = std::make_shared<ImageButton>(window);
		ib->setText("text of image button");
		ib->getImage().setTexture("life");
		ib->getBackground().setColor(sf::Color::Yellow);
		//	ib.setBorder(Border(sf::Color::Green, 1));
		ib->addClickListener(View::ClickHandler::Listener([et, &mainLayout, &window](View& view) {

		}));
		mainLayout.addView(ib);
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
				//cout << "m.x=" << worldPos.x << ", m.y=" << worldPos.y << endl;
			}
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

sf::Color randColor() {
	return sf::Color(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF);
}

void testCleanScreen() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainLayout.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainLayout.draw();
		window.display();
	}
}

#endif // MATANEL_TESTS