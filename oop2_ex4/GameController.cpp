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
#include "AreaButton.h"
#include "WinScreen.h"
#include "LoseScreen.h"
#include "ServerPlayer.h"
#include "ClientPlayer.h"

GameController::GameController()
{ }

void GameController::run()
{
	// create window
	sf::RenderWindow window(sf::VideoMode(1000, 500), "6 Colors");
	window.setFramerateLimit(60);
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
				// TODO aiPlayer = std::make_shared<RegularAIPlayer>();
			} break;
			case LevelDifficultyButton::LevelDifficulty::SUPER: {
				// TODO aiPlayer = std::make_shared<SuperAIPlayer>();
			} break;
		}
		players.push_back(aiPlayer);
		runGameScreen(levelDiffBt->getWindow(), players);
	});
	chooseAIMScreen.run();
}

void GameController::runGameScreen(sf::RenderWindow& window, std::vector<std::shared_ptr<PlayerBase>>& players)
{
	// timer for screen updates
	Timer screenUpdatesTimer;

	// the players
	std::shared_ptr<PlayerBase> userPlayer = players[0], otherPlayer = players[1];
	
	// create game screen
	GameScreen gameScreen(window);

	

	// wait until players are ready
	gameScreen.getBottomPanel()->disable();
	gameScreen.getGameMenu()->getRestartButton()->disable();
	screenUpdatesTimer.start(30, [&gameScreen, &userPlayer, &otherPlayer]() {
		if (userPlayer->isReadyToGame() && otherPlayer->isReadyToGame())
			gameScreen.close();
	});
	gameScreen.run(screenUpdatesTimer);
	gameScreen.getBottomPanel()->enable();
	gameScreen.getGameMenu()->getRestartButton()->enable();
	gameScreen.open();

	// create and play game
	createGame(gameScreen, players);
	playGame(screenUpdatesTimer, gameScreen, players);
	
	gameScreen.getGameMenu()->getExitButton()->addClickListener([&gameScreen](GUI::View& view) {
		gameScreen.close();
	});
	gameScreen.getGameMenu()->getRestartButton()->addClickListener([this, &screenUpdatesTimer, &gameScreen, &players](GUI::View& view) {
		// create and play game
		createGame(gameScreen, players);
		playGame(screenUpdatesTimer, gameScreen, players);
	});
	gameScreen.run(screenUpdatesTimer);
}

void GameController::createGame(GameScreen& gameScreen, std::vector<std::shared_ptr<PlayerBase>>& players, bool userStartbottomLeftVertex)
{
	// clean players info (shapes)
	for (auto& player : players)
		player->clean();

	// the players
	std::shared_ptr<PlayerBase>& userPlayer = players[0], &otherPlayer = players[1];

	// connect to game
	userPlayer->connectToGame(&gameScreen, otherPlayer);
	otherPlayer->connectToGame(&gameScreen, userPlayer);

	// set board
	gameScreen.getBoard()->randomizeBoard(Board::DEFAULT_BOARD_SIZE);
	gameScreen.getGameMenu()->getTurnButton()->setText(userPlayer->getName() + " turn");
	Graph<PolygonView>& graph = gameScreen.getBoard()->getPolygonsGraph();

	// set vertices	
	Graph<PolygonView>::Vertex* topRightVertex = graph.getVertex(gameScreen.getBoard()->getBoardSize().x - 1);
	Graph<PolygonView>::Vertex* bottomLeftVertex = graph.getVertex(graph.getNumOfVertices() - gameScreen.getBoard()->getBoardSize().x);

	if (userStartbottomLeftVertex) {
		otherPlayer->setStartVertex(topRightVertex);
		userPlayer->setStartVertex(bottomLeftVertex);
	}
	else {
		otherPlayer->setStartVertex(bottomLeftVertex);
		userPlayer->setStartVertex(topRightVertex);
	}
	

	// update area percent
	std::shared_ptr<AreaButton>& myAreaBT = gameScreen.getBottomPanel()->getMyAreaButton();
	myAreaBT->updateAreaPercent(static_cast<int>(userPlayer->getPlayerVertices().size()), static_cast<int>(gameScreen.getBoard()->getPolygonsGraph().getNumOfVertices()));
	myAreaBT->setText(myAreaBT->getPreText() + std::to_string(myAreaBT->getAreaPercent()) + "%");
	std::shared_ptr<AreaButton>& rivalAreaBT = gameScreen.getBottomPanel()->getRivalAreaButton();
	rivalAreaBT->updateAreaPercent(static_cast<int>(otherPlayer->getPlayerVertices().size()), static_cast<int>(gameScreen.getBoard()->getPolygonsGraph().getNumOfVertices()));
	rivalAreaBT->setText(rivalAreaBT->getPreText() + std::to_string(rivalAreaBT->getAreaPercent()) + "%");
}

void GameController::playGame(Timer& screenUpdatesTimer, GameScreen& gameScreen, std::vector<std::shared_ptr<PlayerBase>>& players, bool firstPlayerTurn)
// TODO need to get who play first
{
	// the players
	std::shared_ptr<PlayerBase>& userPlayer = players[0], &otherPlayer = players[1];

	bool isFirstPlayerTurn = firstPlayerTurn;

	screenUpdatesTimer.start(30, [&userPlayer, &otherPlayer, &gameScreen, &isFirstPlayerTurn]() {
		if (isFirstPlayerTurn) {
			if (userPlayer->isReadyToPlay()) {
				sf::Color selectedColor = userPlayer->selectColor();
				ColoringAlgorithm colorAlgo;
				colorAlgo.colorGraph(userPlayer->getPlayerVertices(), userPlayer->getBorderVertices(), selectedColor);

				gameScreen.getBottomPanel()->getColorPanel()->disable();
				isFirstPlayerTurn = false;
				gameScreen.getGameMenu()->getTurnButton()->setText(otherPlayer->getName() + " turn");
				
				// update area percent
				std::shared_ptr<AreaButton>& myAreaBT = gameScreen.getBottomPanel()->getMyAreaButton();
				myAreaBT->updateAreaPercent(static_cast<int>(userPlayer->getPlayerVertices().size()), static_cast<int>(gameScreen.getBoard()->getPolygonsGraph().getNumOfVertices()));
				myAreaBT->setText(myAreaBT->getPreText() + std::to_string(myAreaBT->getAreaPercent()) + "%");

				// check if user win
				if (myAreaBT->getAreaPercent() >= AreaButton::WIN_NUM_PRECENTS) {
					gameScreen.close();
					WinScreen winScreen(gameScreen.getWindow());
					winScreen.getBackToMenuBT()->addClickListener([&winScreen](GUI::View& view) {
						winScreen.close();
					});
					winScreen.run();
				}
			}
		}
		else {
			if (otherPlayer->isReadyToPlay()) {
				if (otherPlayer->isReadyToPlay()) {
					sf::Color selectedColor = otherPlayer->selectColor();
					ColoringAlgorithm colorAlgo;
					colorAlgo.colorGraph(otherPlayer->getPlayerVertices(), otherPlayer->getBorderVertices(), selectedColor);
					gameScreen.getBottomPanel()->getColorPanel()->enable();
					isFirstPlayerTurn = true;
					gameScreen.getGameMenu()->getTurnButton()->setText(userPlayer->getName() + " turn");
					
					// update area percent
					std::shared_ptr<AreaButton>& rivalAreaBT = gameScreen.getBottomPanel()->getRivalAreaButton();
					rivalAreaBT->updateAreaPercent(static_cast<int>(otherPlayer->getPlayerVertices().size()), static_cast<int>(gameScreen.getBoard()->getPolygonsGraph().getNumOfVertices()));
					rivalAreaBT->setText(rivalAreaBT->getPreText() + std::to_string(rivalAreaBT->getAreaPercent()) + "%");

					// check if user lose
					if (rivalAreaBT->getAreaPercent() >= AreaButton::WIN_NUM_PRECENTS) {
						gameScreen.close();
						LoseScreen loseScreen(gameScreen.getWindow());
						loseScreen.getBackToMenuBT()->addClickListener([&loseScreen](GUI::View& view) {
							loseScreen.close();
						});
						loseScreen.run();
					}
				}
			}
		}
	});
}

void GameController::runJoinScreen(sf::RenderWindow& window)
{
	// timer for screen updates
	Timer screenUpdatesTimer;

	// create requests queues
	RequestsQueue<int> sendRequests, receiveRequests;

	// create client thread
	RequestsClientThread clientThread(sendRequests, receiveRequests);

	// create server player
	std::shared_ptr<ServerPlayer> clientPlayer = std::make_shared<ServerPlayer>(clientThread);

	// create screen
	JoinGameScreen joinGameScreen(window);

	screenUpdatesTimer.start(30, [this, &clientThread, &clientPlayer, &joinGameScreen]() {
		// check if client connected
		if (clientThread.isConnectedToServer()) {
			// run game screen
			std::vector<std::shared_ptr<PlayerBase>> players;
			players.push_back(std::make_shared<UserPlayer>());
			players.push_back(clientPlayer);
			runGameScreen(joinGameScreen.getWindow(), players);
			joinGameScreen.close();
		}
	});

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
	RequestsQueue<int> sendRequests, receiveRequests;

	// create server
	RequestsServerThread serverThread(sendRequests, receiveRequests);
	serverThread.start(INetworkThread::DEFAULT_PORT);

	// create client player
	std::shared_ptr<ClientPlayer> clientPlayer = std::make_shared<ClientPlayer>(serverThread);

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

	waitMultScreen.getStartButton()->addClickListener([this, &clientPlayer, &waitMultScreen](GUI::View& view) {
		std::vector<std::shared_ptr<PlayerBase>> players;
		players.push_back(std::make_shared<UserPlayer>());
		players.push_back(clientPlayer);
		runGameScreen(view.getWindow(), players);
		waitMultScreen.close();
	});
	waitMultScreen.run(screenUpdatesTimer);
	
	// stop server thread
	serverThread.stop();
}
