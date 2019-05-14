#include "GameController.h"
#include "MainScreen.h"
#include "ChooseAIModeScreen.h"
#include "GameScreen.h"
#include "JoinGameScreen.h"
#include "WaitingMultiplayerScreen.h"
#include "RequestsClientThread.h"
#include "RequestsServerThread.h"
#include "Timer.h"
#include "Logger.h"
#include "PlayerAIStupid.h"
#include "UserPlayer.h"
#include "ColoringAlgorithm.h"

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
		runWaitMultScreen(view.getWindow());
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

		// create players
		std::vector<std::shared_ptr<PlayerBase>> players;
		players.push_back(std::make_shared<UserPlayer>());
		std::shared_ptr<PlayerBase> aiPlayer;

		switch (levelDiffBt->getLevelDifficulty())
		{
			case LevelDifficultyButton::LevelDifficulty::STUPID: {
				aiPlayer = std::make_shared<PlayerAIStupid>();	
			} break;
			case LevelDifficultyButton::LevelDifficulty::REGULAR: {
				//aiPlayer = std::make_shared<RegularAIPlayer>();
			} break;
			case LevelDifficultyButton::LevelDifficulty::SUPER: {
				//aiPlayer = std::make_shared<SuperAIPlayer>();
			} break;
		}
		players.push_back(aiPlayer);
		runGameScreen(levelDiffBt->getWindow(), players);
	});
	chooseAIMScreen.run();
}

void GameController::runGameScreen(sf::RenderWindow& window, std::vector<std::shared_ptr<PlayerBase>>& players)
{
	bool isFirstPlayerTurn = true;

	ColoringAlgorithm colorAlgo;



	// timer for screen updates
	Timer screenUpdatesTimer;

	std::shared_ptr<PlayerBase> userPlayer = players[0], otherPlayer = players[1];
	
	GameScreen gameScreen(window);
	gameScreen.getBoard()->randomizeBoard({ 8,8 }); // TODO: remove this line

	for (auto player : players)
		player->connectToGame(&gameScreen);

	Graph<PolygonView>& graph = gameScreen.getBoard()->getPolygonsGraph();
	userPlayer->setStartVertex(graph.getVertex(graph.getNumOfVertices() - gameScreen.getBoard()->getBoardSize().x));
	otherPlayer->setStartVertex(graph.getVertex(gameScreen.getBoard()->getBoardSize().x-1));

	screenUpdatesTimer.start(30, [&]() {
		if (isFirstPlayerTurn) {
			if (userPlayer->isReadyToPlay()) {
				sf::Color selectedColor = userPlayer->selectColor();
				colorAlgo.colorGraph(userPlayer->getPlayerVertices(), userPlayer->getBorderVertices(), selectedColor);

				gameScreen.getBottomPanel()->getColorPanel()->disable();
				isFirstPlayerTurn = false;
			}
		}
		else {
			if (otherPlayer->isReadyToPlay()) {
				if (otherPlayer->isReadyToPlay()) {
					sf::Color selectedColor = otherPlayer->selectColor();
					colorAlgo.colorGraph(otherPlayer->getPlayerVertices(), otherPlayer->getBorderVertices(), selectedColor);
					LOG(std::to_string(selectedColor.toInteger()));
					gameScreen.getBottomPanel()->getColorPanel()->enable();
					isFirstPlayerTurn = true;
				}
			}
		}
	});

	
	gameScreen.getGameMenu()->getExitButton()->addClickListener([&gameScreen](GUI::View& view) {
		gameScreen.close();
	});
	gameScreen.getGameMenu()->getRestartButton()->addClickListener([&gameScreen](GUI::View& view) {
		// TODO restart game here
		sf::Vector2i size = gameScreen.getBoard()->getBoardSize();
		size.x = rand() % 10 + 2;
		size.y = rand() % 10 + 2;
		if (size.y % 2 == 1)
			size.y++;
		gameScreen.getBoard()->randomizeBoard(size);
	});
	gameScreen.run(screenUpdatesTimer);
}

void GameController::runJoinScreen(sf::RenderWindow& window)
{
	// timer for screen updates
	Timer screenUpdatesTimer;

	// create requests queues
	RequestsQueue<string> sendRequests, receiveRequests;

	// create client thread
	RequestsClientThread clientThread(sendRequests, receiveRequests);

	screenUpdatesTimer.start(30, [&clientThread]() {
		// check if client connected
		if (clientThread.isConnectedToServer()) {
			// TODO run game screen
		}
	});

	// create screen
	JoinGameScreen joinGameScreen(window);
	joinGameScreen.getConnectButton()->addClickListener([this, &clientThread, &joinGameScreen](GUI::View& view) {
		joinGameScreen.setAsConnecting();
		// connect to server
		sf::IpAddress serverIpAddress(joinGameScreen.getIpEditText()->getText());
		clientThread.start(serverIpAddress, INetworkThread::DEFAULT_PORT);
	});
	joinGameScreen.run(screenUpdatesTimer);
	
	// stop client thread
	clientThread.stop();
}

void GameController::runWaitMultScreen(sf::RenderWindow& window)
{
	bool gameIsReady = false;

	// timer for screen updates
	Timer screenUpdatesTimer;

	// create network requests queues
	RequestsQueue<string> sendRequests, receiveRequests;

	// create server
	RequestsServerThread serverThread(sendRequests, receiveRequests);
	serverThread.start(INetworkThread::DEFAULT_PORT);

	// create screen
	WaitingMultiplayerScreen waitMultScreen(window);

	screenUpdatesTimer.start(30, [&serverThread, &waitMultScreen, &gameIsReady]() {		
		if (!gameIsReady) {
			// check if client connected
			if (serverThread.getNumOfClients() == 1) {
				// update components
				serverThread.setBlockConnections(true);
				waitMultScreen.setReadyToPlay();
				gameIsReady = true;
			}
		}		
	});

	waitMultScreen.getStartButton()->addClickListener([](GUI::View& view) {
		// TODO open game screen
	});
	waitMultScreen.run(screenUpdatesTimer);
	
	// stop server thread
	serverThread.stop();
}
