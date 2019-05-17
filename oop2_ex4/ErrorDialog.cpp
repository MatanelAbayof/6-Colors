//---- include section ------
#include "ErrorDialog.h"
#include "SoundManager.h"

void GUI::ErrorDialog::show(const string& errorMessage)
{
	// create window
	sf::RenderWindow window(sf::VideoMode(1200, 100), "");
	// create error dialog
	ErrorDialog errorDialog(window, errorMessage);
	// run alert dialog
	errorDialog.runWindow();
}

string GUI::ErrorDialog::toString() const
{
	return "ErrorDialog: { " + AlertDialog::toString() + " }";
}

GUI::ErrorDialog::ErrorDialog(sf::RenderWindow& window, const string& errorMessage)
	: AlertDialog(window, "Error", errorMessage, AlertDialog::BT_TEXT_OK)
{
	initComponents();
}

void GUI::ErrorDialog::initComponents()
{	
	// play error sound
	SoundManager::getInterface().playSound("error");
}
