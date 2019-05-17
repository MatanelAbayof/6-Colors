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
	// set level difficulty
	void setLevelButton(LevelDifficulty level);
	// get level difficulty
	LevelDifficulty getLevelDifficulty() const { return m_levelDiff; }
private:
	// init
	void init();
	// level difficulty
	LevelDifficulty m_levelDiff;
};

