/*
 * main for tests
 */
//#define MATANEL_TESTS
#ifdef MATANEL_TESTS

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
#pragma endregion

#pragma region Usings
//-------------- using section -----------------
using namespace GUI;
#pragma endregion

#pragma region Declarations
//-------------- declare functions -------------
sf::Color randColor();
void testGUI();
void testFirstTime();
#pragma endregion

//--------------  main -------------------------
int main()
{
	std::cout << "Hello Akiva World!\n";

	try
	{
		testFirstTime();
		//testGUI();
	}
	catch (const std::exception& ex)
	{
		// Oh No! error...
		ErrorDialog::show(ex.what());
	}
}

void testFirstTime() {
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "testFirstTime");

	// create root view
	VerticalLayout<Button> mainLayout(window);
	mainLayout.makeRootView();
	mainLayout.getBackground().setColor(sf::Color::Blue);
	mainLayout.getBorder().setSize(2.f);
	mainLayout.getBorder().setColor(sf::Color::Cyan);


	// add button
	std::shared_ptr<Button> bt1 = std::make_shared<Button>(window, "Bt1");
	bt1->getBorder().setSize(1.f);
	bt1->getBorder().setColor(sf::Color::Red);
	bt1->addClickListener([&bt1](View& view) {
		bt1->hide();
	});
	mainLayout.addView(bt1);
	std::shared_ptr<Button> bt2 = std::make_shared<Button>(window, "Bt2");
	mainLayout.addView(bt2);

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


#endif // MATANEL_TESTS