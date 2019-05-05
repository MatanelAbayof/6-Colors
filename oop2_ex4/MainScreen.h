#pragma once
//---- include section ------
#include <string>
#include "BaseScreen.h"
#include "RelativeLayout.h"
#include "Button.h"
#include "TextView.h"

//---- using section --------
using std::string;

namespace GUI {
	/*
	 * MainScreen class
	 */
	class MainScreen :
		public BaseScreen<GUI::RelativeLayout<View>>
	{
	public:
		// constructor
		explicit MainScreen(sf::RenderWindow& window);
		// destructor
		~MainScreen() = default;
		//get certin button
		const std::shared_ptr<Button>& getSingleBt();
		const std::shared_ptr<Button>& getCreateBt();
		const std::shared_ptr<Button>& getJoinBt();
		const std::shared_ptr<Button>& getExitleBt();
		// convert to string
		virtual string toString() const override;
	private:
		// menu title
		std::shared_ptr <TextView> m_menuTitle;
		// buttons
		std::shared_ptr <Button> m_singlePlayerBt, m_createGameBt, m_joinGameBt, m_exitBt;
		// init buttons
		void init();
	};
}



/*Shared_ptr<Button> m_singlePlayerBt, m_createGameBt, m_joinGameBt, m_exitBt*/

