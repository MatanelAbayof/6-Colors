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
		bool isClosed() const { return m_closeFlag; }
		// run the screen
		void run();
		// convert to string
		virtual string toString() const override { return "BaseScreen: { " + ViewType::toString() + " }"; }
	protected:
		// constructor
		explicit BaseScreen(sf::RenderWindow& window);
		// destructor
		virtual ~BaseScreen() {}
		// close flag
		bool m_closeFlag;
	};

	template<class ViewType>
	void BaseScreen<ViewType>::run()
	{
		while (ViewType::getWindow().isOpen() && !isClosed())
		{
			sf::Event event;
			while (ViewType::getWindow().pollEvent(event))
			{
				ViewType::handleEvent(event);
				if (event.type == sf::Event::Closed)
					ViewType::getWindow().close();
			}

			ViewType::getWindow().clear();
			ViewType::draw();
			ViewType::getWindow().display();
		}
	}

	template<class ViewType>
	BaseScreen<ViewType>::BaseScreen(sf::RenderWindow& window)
		: ViewType(window), m_closeFlag(false)
	{
		ViewType::getBackground().setColor(sf::Color(146, 205, 255));
		ViewType::makeRootView();
		ViewType::addKeyDownListener([this](sf::Keyboard::Key& key) {
			if(key == sf::Keyboard::Escape)
				close();
		});
	}
}
