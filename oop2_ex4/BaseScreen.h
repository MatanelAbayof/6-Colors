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
		// convert to string
		virtual string toString() const { return "BaseScreen: { " + ViewType::toString() + " }"; }
	protected:
		// constructor
		explicit BaseScreen(sf::RenderWindow& window) :ViewType(window) {}
		// destructor
		virtual ~BaseScreen() {}
	};
}
