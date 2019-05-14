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
	// get game screen
	const std::shared_ptr<GameScreen>& getGameScreen() const { return m_gameScreen; }
	// set player name
	void setName(const string& name) { m_name = name; }
	// check if the player is ready to play
	virtual bool isReadyToPlay() = 0;
	// convert to string
	virtual string toString() const;
protected:
	// constructor
	PlayerBase();
private:
	// player name
	string m_name;
	// list of the player vertexs
	std::unordered_set<GraphVertex> m_playerVertexs;
	// list of border vertexs
	std::unordered_set<GraphVertex> m_borderVertexs;
	//gmae screen
	std::shared_ptr<GameScreen> m_gameScreen;
};

