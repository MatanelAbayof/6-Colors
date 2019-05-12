#include "GameController.h"
#include "MainScreen.h"
#include "ChooseAIModeScreen.h"
#include "GameScreen.h"

GameController::GameController()
{
}

void GameController::run()
{
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "6 Colors");

	runMainScreen(window);
}

string GameController::toString() const
{
	return "GameController: { }";
}

void GameController::runMainScreen(sf::RenderWindow& window)
{
	MainScreen mainScreen(window);

	mainScreen.getSingleBt()->addClickListener([this](GUI::View& view) {
		runChooseModeAIScreen(view.getWindow());
	});
	mainScreen.getExitleBt()->addClickListener([this, &mainScreen](GUI::View& view) {
		mainScreen.close();
	});

	while (window.isOpen() && !mainScreen.isClosed())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			mainScreen.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		mainScreen.draw();
		window.display();
	}
}

void GameController::runChooseModeAIScreen(sf::RenderWindow& window)
{
	ChooseAIModeScreen chooseAIMScreen(window);

	chooseAIMScreen.getDuperAIbt()->addClickListener([this](GUI::View& view) {
		runGameScreen(view.getWindow());
	});
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			chooseAIMScreen.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		chooseAIMScreen.draw();
		window.display();
	}
}

void GameController::runGameScreen(sf::RenderWindow& window)
{
	GameScreen gameScreen(window);

	gameScreen.getBoard()->randomizeBoard({ 8,8 });

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			gameScreen.handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		gameScreen.draw();
		window.display();
	}
}
