#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "Board.h"
#include "GameMenu.h"
#include "BottomPanel.h"
#include "RelativeLayout.h"

//---- using section --------
using std::string;
using BSGameScreen = GUI::BaseScreen<GUI::RelativeLayout<GUI::View>>;

/*
 * GameScreen class
 */
class GameScreen 
	: public BSGameScreen
{
public:
	// constructor
	explicit GameScreen(sf::RenderWindow& window);
	// destructor
	virtual ~GameScreen() = default;
	const std::shared_ptr<GameMenu>& getGameMenu() const { return m_gameMenu; }
	const std::shared_ptr<Board>& getBoard() const { return m_board; }
	const std::shared_ptr<BottomPanel>& getBottomPanel() const { return m_bottomPanel; }
	// convert to string
	virtual string toString() const override;
private:
	std::shared_ptr<GameMenu> m_gameMenu;
	std::shared_ptr<Board> m_board;
	std::shared_ptr<BottomPanel> m_bottomPanel;
	// init
	void init();
};

