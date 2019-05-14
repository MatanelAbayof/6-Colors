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
	using GraphVertex = Graph<PolygonView>::Vertex*;
	// when a player want to select a color
	virtual sf::Color selectColor() = 0;
	// get player name
	const string& getName() const { return m_name; }
	// set game screen
	virtual void connectToGame(GameScreen* gameScreen) { m_gameScreen = gameScreen; }
	// get game screen
	GameScreen* getGameScreen();
	// get list of the player vertices
	std::unordered_set<GraphVertex>& getPlayerVertices() { return m_playerVertices; }
	// get list of border vertices
	std::unordered_set<GraphVertex>& getBorderVertices() { return m_borderVertices; }
	// set player name
	void setName(const string& name) { m_name = name; }
	// set start vertex
	void setStartVertex(GraphVertex vertex);
	// check if the player is ready to play
	virtual bool isReadyToPlay() const = 0;
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	PlayerBase();
private:
	// player name
	string m_name;
	// list of the player vertices
	std::unordered_set<GraphVertex> m_playerVertices;
	// list of border vertices
	std::unordered_set<GraphVertex> m_borderVertices;
	//gmae screen
	GameScreen* m_gameScreen;
};

