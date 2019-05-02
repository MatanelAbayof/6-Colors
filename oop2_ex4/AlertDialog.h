#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include "View.h"
#include "TextView.h"
#include "Button.h"
#include "VerticalLayout.h"
#include <string>
#include <memory>

//---- using section --------
using std::string;

namespace GUI {

/*
 * AlertDialog class
*/
class AlertDialog
{
public:
	// button text OK
	static const string BT_TEXT_OK;
	// show new message box
	static void show(const string& title, const string& message, const string& btText);
	// get button
	std::shared_ptr<Button> getButton() const { return m_button; }
	// convert to string
	virtual string toString() const;
protected:
	// run window
	void runWindow();
	// constructor
	explicit AlertDialog(sf::RenderWindow& window, const string& title, const string& message, const string& btText);
private:
	// content of message
	std::shared_ptr<VerticalLayout<GUI::View>> m_content;
	// message
	std::shared_ptr<TextView> m_message;
	// button
	std::shared_ptr<Button> m_button;
	// init components
	void initComponents(sf::RenderWindow& window, const string& title, const string& message, const string& btText);
};

}
