#pragma once
#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "LevelDifficultyButton.h"

//---- using section --------
using std::string;

/*
 * WaitingMultiplayerScreen class
 */

class ChooseAIModeScreen :
	public GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>
{
public:
	// constructor
	explicit ChooseAIModeScreen(sf::RenderWindow& window);
	// destructor
	virtual ~ChooseAIModeScreen() = default;
	// get buttons
	const std::shared_ptr<LevelDifficultyButton>& getStupidAIbt() const { return m_stupidAIBt; }
	const std::shared_ptr<LevelDifficultyButton>& getRegularAIbt() const { return m_regularAIBt; }
	const std::shared_ptr<LevelDifficultyButton>& getSuperAIbt() const { return m_superAIBt; }
	// add level click listener
	void addLevelClickListener(std::function<void(std::shared_ptr<LevelDifficultyButton>)> onClickBT);
	// convert to string
	virtual string toString() const override;
private:
	// level button
	std::shared_ptr<LevelDifficultyButton> m_stupidAIBt, m_regularAIBt, m_superAIBt;
	// init Component
	void initComponents();
};

