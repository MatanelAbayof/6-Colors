#pragma once
//---- include section ------
#include <string>
#include <unordered_set>
#include <SFML/Graphics/Color.hpp>

//---- using section --------
using std::string;

/*
 * PlayerBase abstract class
 */
class PlayerBase
{
public:
	virtual sf::Color selectColor() = 0;
	const string& getName() const;
	void setName(const string& name);
	virtual bool isReadyToPlay() = 0;
	// convert to string
	virtual string toString() const;
private:
	// constructor
	PlayerBase();
	// destructor
	~PlayerBase();
	string m_name;
	//std::unordered_set<Shape*> m_filldsShapes;
};

