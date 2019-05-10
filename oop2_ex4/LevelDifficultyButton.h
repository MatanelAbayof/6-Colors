#pragma once
//---- include section ------
#include <string>
#include "ImageButton.h"

//---- using section --------
using std::string;

/*
 * LevelDifficultyButton class
 */
class LevelDifficultyButton :
	public GUI::ImageButton
{
public:
	// level difficulty
	enum LevelDifficulty { STUPID, REGULAR, SUPER };
	// constructor
	explicit LevelDifficultyButton(sf::RenderWindow& window, const string& text = "");
	//convert to string
	virtual string toString() const override;
	//
	void setLevel(LevelDifficulty level);
private:
	// init
	void init();
	LevelDifficulty m_levelDiff;
};

