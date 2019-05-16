#pragma once
//---- include section ------
#include <string>
#include "View.h"
#include "Timer.h"
#include "SoundManager.h"

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
		// open
		void open() { m_closeFlag = false; }
		// check if screen is closed
		bool isClosed() const { return m_closeFlag; }
		// run the screen
		void run();
		// run the screen and listen to updates with timer
		void run(Timer& timer);
		// destructor
		virtual ~BaseScreen() = default;
		// convert to string
		virtual string toString() const override { return "BaseScreen: { " + ViewType::toString() + " }"; }
	protected:
		// close flag
		bool m_closeFlag;
		// constructor
		explicit BaseScreen(sf::RenderWindow& window);
		// run the screen and listen to updates with timer
		void run(Timer* timer);
	};

	template<class ViewType>
	void BaseScreen<ViewType>::run()
	{
		run(nullptr); // run without timer
	}

	template<class ViewType>
	void BaseScreen<ViewType>::run(Timer& timer)
	{
		run(&timer);
	}

	template<class ViewType>
	BaseScreen<ViewType>::BaseScreen(sf::RenderWindow& window)
		: ViewType(window), m_closeFlag(false)
	{
		ViewType::getBackground().setColor(sf::Color(146, 205, 255));
		ViewType::makeRootView();
		ViewType::addKeyDownListener([this](sf::Keyboard::Key& key) {
			if(key == sf::Keyboard::Escape) {
				close();
				SoundManager::getInterface().playSound("window_close");
			}
		});
	}
	template<class ViewType>
	void BaseScreen<ViewType>::run(Timer* timer)
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

			// update timer if needed
			if (timer != nullptr)
				timer->checkTimer();
		}
	}
}
