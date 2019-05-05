//---- include section ------
#include "AlertDialog.h"

// init
const string GUI::AlertDialog::BT_TEXT_OK = "OK";

void GUI::AlertDialog::show(const string& title, const string& message, const string& btText)
{
	// create window
	sf::RenderWindow window(sf::VideoMode(500, 100), "");
	// create alert dialog
	AlertDialog alertDialog(window, title, message, btText);

	// run alert dialog
	alertDialog.runWindow();
}

string GUI::AlertDialog::toString() const
{
	return "AlertDialog: { " + m_content->toString() + " }";
}

GUI::AlertDialog::AlertDialog(sf::RenderWindow& window, const string& title, const string& message, const string& btText)
{	
	initComponents(window, title, message, btText);
}

void GUI::AlertDialog::initComponents(sf::RenderWindow& window, const string& title, const string& message, const string& btText)
{
	window.setTitle(title);

	// create views
	m_content = std::make_shared<VerticalLayout<View>>(window);
	m_message = std::make_shared<TextView>(window);
	m_button = std::make_shared<Button>(window);

	m_message->setText(message);
	m_button->setText(btText);

	m_content->getBackground().setColor(sf::Color(234, 234, 234));
	m_content->makeRootView();

	// init background color of button with events
	sf::Color btBackColor(183, 183, 183), btEnterBackColor(120, 120, 120);
	m_button->getBackground().setColor(btBackColor);
	m_button->addEnterListener(View::EnterHandler::Listener([btEnterBackColor](View &view) {
		view.getBackground().setColor(btEnterBackColor);
	}));
	m_button->addLeaveListener(View::LeaveHandler::Listener([btBackColor](View &view) {
		view.getBackground().setColor(btBackColor);
	}));

	m_content->addView(m_message);
	m_content->addView(m_button);
}

void GUI::AlertDialog::runWindow()
{
	// get window
	sf::RenderWindow& window = m_content->getWindow();

	// flag for ready to close
	bool readyToClose = false;

	m_button->addClickListener(View::ClickHandler::Listener([&readyToClose](View &view) {
		readyToClose = true;
	}));

	// run window
	while (window.isOpen())
	{
		if (readyToClose)
			window.close();

		sf::Event event;
		while (window.pollEvent(event))
		{
			m_content->handleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		m_content->draw();
		window.display();
	}
}
