#pragma once
//---- include section ------
#include <string>
#include <unordered_set>
#include <SFML/Graphics/Color.hpp>
#include "Shape.h"
#include "Graph.h"
#include "PolygonView.h"
#include "GameScreen.h"

//---- using section --------
using std::string;

/*
 * PlayerBase abstract class
 */
class PlayerBase
{
public:
	// vertex of graph
	using GraphVertex = Graph<PolygonView>::Vertex*;
	// when a player want to select a color
	virtual sf::Color selectColor() = 0;
	// get player name
	const string& getName() const { return m_name; }
	// connect to game screen
	virtual void connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer);
	// get game screen
	GameScreen* getGameScreen();
	// get list of the player vertices
	std::unordered_set<GraphVertex>& getPlayerVertices() { return m_playerVertices; }
	// get list of border vertices
	std::unordered_set<GraphVertex>& getBorderVertices() { return m_borderVertices; }
	// set player name
	void setName(const string& name) { m_name = name; }
	// set start vertex
	virtual void setStartVertex(GraphVertex vertex);
	// get last color
	const sf::Color& getLastColor() const { return m_lastColor; }
	// get forbidden colors
	std::vector<sf::Color> getForbiddenColors() const;
	// event on other player played
	virtual void onOtherPlayerPlayed(const sf::Color& selectedColor) = 0;
	// event on player played
	virtual void onPlayerPlayed(const sf::Color& selectedColor) = 0;
	// check if the player is ready to play
	virtual bool isReadyToPlay() const = 0;
	// get rival player
	const std::shared_ptr<PlayerBase>& getRivalPlayer() const { return m_rivalPlayer; }
	// clean
	void clean();
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	PlayerBase();
	// set last color
	void setLastColor(sf::Color lastColor) { m_lastColor = lastColor; };
private:
	// last color
	sf::Color m_lastColor;
	// player name
	string m_name;
	// list of the player vertices
	std::unordered_set<GraphVertex> m_playerVertices;
	// list of border vertices
	std::unordered_set<GraphVertex> m_borderVertices;
	//game screen
	GameScreen* m_gameScreen;
	// rival player
	std::shared_ptr<PlayerBase> m_rivalPlayer;
};