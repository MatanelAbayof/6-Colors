#pragma once
//---- include section ------
#include <string>
#include "View.h"

//---- using section --------
using std::string;

namespace GUI {
	/*
	 * BaseScreen abstract class
	 */
	template <class ViewType = GUI::View>
	class BaseScreen
		: public ViewType
	{
	public:
		// close screen
		void close() { m_closeFlag = true; }
		// check if screen is closed
		bool isClosed() const { return m_closeFlag;  }
		// convert to string
		virtual string toString() const { return "BaseScreen: { " + ViewType::toString() + " }"; }
	protected:
		// constructor
		explicit BaseScreen(sf::RenderWindow& window);
		// destructor
		virtual ~BaseScreen() {}
		// close flag
		bool m_closeFlag;
	};

	template<class ViewType>
	BaseScreen<ViewType>::BaseScreen(sf::RenderWindow& window)
		: ViewType(window), m_closeFlag(false)
	{
		ViewType::getBackground().setColor(sf::Color(146, 205, 255));
		ViewType::makeRootView();
	}
}
