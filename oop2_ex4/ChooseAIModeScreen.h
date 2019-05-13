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
	const std::shared_ptr<LevelDifficultyButton>& getDuperAIbt() const { return m_superAIBt; }
	// convert to string
	virtual string toString() const override;
private:
	// waiting and IP signs
	std::shared_ptr<LevelDifficultyButton> m_stupidAIBt, m_regularAIBt, m_superAIBt;
	// init Component
	void initComponents();
};

