#include "GameController.h"
#include "MainScreen.h"
#include "ChooseAIModeScreen.h"
#include "GameScreen.h"
#include "JoinGameScreen.h"

GameController::GameController()
{ }

void GameController::run()
{
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "6 Colors");
	// run main screen
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
	mainScreen.getCreateBt()->addClickListener([this](GUI::View& view) {
		// TODO run waiting screen
	});
	mainScreen.getJoinBt()->addClickListener([this](GUI::View& view) {
		runJoinScreen(view.getWindow());
	});
	mainScreen.getExitleBt()->addClickListener([this, &mainScreen](GUI::View& view) {
		mainScreen.close();
	});
	mainScreen.run();
}

void GameController::runChooseModeAIScreen(sf::RenderWindow& window)
{
	ChooseAIModeScreen chooseAIMScreen(window);
	chooseAIMScreen.addLevelClickListener([this](std::shared_ptr<LevelDifficultyButton> levelDiffBt) {
		switch (levelDiffBt->getLevelDifficulty())
		{
			case LevelDifficultyButton::LevelDifficulty::STUPID: {
				runGameScreen(levelDiffBt->getWindow()); // TODO remove this line
			} break;
			case LevelDifficultyButton::LevelDifficulty::REGULAR: {
				// TODO
			} break;
			case LevelDifficultyButton::LevelDifficulty::SUPER: {
				// TODO
			} break;
		}
	});
	chooseAIMScreen.run();
}

void GameController::runGameScreen(sf::RenderWindow& window)
{
	GameScreen gameScreen(window);
	gameScreen.getBoard()->randomizeBoard({ 8,8 }); // TODO: remove this line
	gameScreen.getGameMenu()->getExitButton()->addClickListener([&gameScreen](GUI::View& view) {
		gameScreen.close();
	});
	gameScreen.getGameMenu()->getRestartButton()->addClickListener([&gameScreen](GUI::View& view) {
		sf::Vector2i size = gameScreen.getBoard()->getBoardSize();
		size.x = rand() % 10 + 2;
		size.y = rand() % 10 + 2;
		if (size.y % 2 == 1)
			size.y++;
		gameScreen.getBoard()->randomizeBoard(size);
	});
	gameScreen.run();
}

void GameController::runJoinScreen(sf::RenderWindow& window)
{
	JoinGameScreen joinGameScreen(window);
	joinGameScreen.getConnectButton()->addClickListener([this](GUI::View& view) {
		// TODO 
	});
	joinGameScreen.run();
}
