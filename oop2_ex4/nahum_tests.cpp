/*
 * main for tests
 */
#include "main_tests.h"
#ifdef NAHUM_TESTS

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

#pragma region Includes
//-------------- include section --------------
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp> // JSON library
#include <iostream>
#include "View.h"
#include "VerticalLayout.h"
#include "EditText.h"
#include "ImageButton.h"
#include "ErrorDialog.h"
#include "GameMenu.h"
#include "ColorButton.h"
#include "ColorPanel.h"
#include "BottomPanel.h"
#include "PolygonView.h"
#include "Square.h"
#include "Board.h"
#include "Utilities.h"
#include "ChooseAIModeScreen.h"
#pragma endregion

#pragma region Usings
//-------------- using section -----------------
using namespace GUI;
#pragma endregion

#pragma region Declarations
//-------------- declare functions -------------
sf::Color randColor();
void testBoard();
void testShape();
void testGUI();
void testGameMenu();
void testChooseScreen();
#pragma endregion

//--------------  main -------------------------
void nahum_main()
{
	std::cout << "Hello Nahum World!\n";

	try
	{
		testChooseScreen();
		//testBoard();
		//testShape();
		//testGameMenu();
		//testGUI();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
	}
}

void testChooseScreen() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);

	std::shared_ptr<ChooseAIModeScreen> cm = std::make_shared<ChooseAIModeScreen>(window);
	mainLayout.addView(cm);

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

void testBoard() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "Screen");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::White);
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(1.f);


	std::shared_ptr<Board> board = std::make_shared<Board>(window);
	board->randomizeBoard(sf::Vector2i{ 20, 20 });
	mainLayout.addView(board);


	for (int i = 0; i < board->getNumOfViews(); ++i) {
		auto& p = board->getView(i);
		p->addKeyDownListener([&p, &board](sf::Keyboard::Key& key) {
			if (key == sf::Keyboard::A)
				p->setColor(Utilities::randColor());
		});
	}

	board->addKeyDownListener([&board](sf::Keyboard::Key& key) {
		if (key == sf::Keyboard::S) {
			sf::Vector2i size = board->getBoardSize();
			size.x = rand() % 10 + 2;
			size.y = rand() % 10 + 2;
			if (size.y % 2 == 1)
				size.y++;
			board->randomizeBoard(size);
		}
	});

	board->addClickListener([&board](View& view) {
		std::cout << view.toString() << std::endl;
	});

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

void testShape() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "GUI");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(3);
	//mainLayout.setBorder(Border(sf::Color::Blue, 5));
	mainLayout.getBackground().setColor(sf::Color::Blue);

	std::unique_ptr<Square> sq = std::make_unique<Square>(sf::Color::Yellow);
	std::cout << sq->toString();
	std::shared_ptr<PolygonView> polygonView = std::make_shared<PolygonView>(window, std::move(sq));
	mainLayout.addView(polygonView);

	polygonView->addClickListener([&polygonView, &sq](View& view) {
		std::cout << polygonView->toString();
	});
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

void testGameMenu() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "GUI");

	// create root view
	VerticalLayout<> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBorder().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(3);
	//mainLayout.setBorder(Border(sf::Color::Blue, 5));
	mainLayout.getBackground().setColor(sf::Color::Blue);
	
	// add edit text
	std::shared_ptr<GameMenu> et = std::make_shared<GameMenu>(window);
	std::shared_ptr<BottomPanel> bp = std::make_shared<BottomPanel>(window);
	mainLayout.addView(et);
	mainLayout.addView(bp);
	std::shared_ptr<ColorPanel> cp = bp->getColorPanel();
	const sf::Color color = sf::Color::Black;
	for (auto c : ColorPanel::COLORS) {
		std::shared_ptr<ColorButton> cb = cp->getColorButton(c);
		std::cout << cb->toString() << std::endl;
	}
	
	cp->addClickColorListener([](std::shared_ptr<ColorButton> colorButton) {
		std::cout << colorButton->toString() << std::endl;
	});
	
	bp->addClickListener([&bp](View& view){ 
		bp->getMyAreaButton()->setAreaPercent(bp->getMyAreaButton()->getAreaPercent() + 3.f);
		std::cout << bp->toString();
	});
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


#endif // NAHUM_TESTS