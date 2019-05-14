#pragma once
//---- include section ------
#include <string>
#include <SFML/Graphics.hpp>

//---- using section --------
using std::string;

/*
 * GameController class
 */
class GameController
{
public:
	// constructor
	GameController();
	// run the game
	void run();
	// convert to string
	virtual string toString() const;
private:
	// run main screen
	void runMainScreen(sf::RenderWindow& window);
	// run chose mode AI screen
	void runChooseModeAIScreen(sf::RenderWindow& window);
	// run game screen
	void runGameScreen(sf::RenderWindow& window);
	// run join screen
	void runJoinScreen(sf::RenderWindow& window);
	// run waiting multiplayer screen
	void runWaitMultScreen(sf::RenderWindow& window);
};

