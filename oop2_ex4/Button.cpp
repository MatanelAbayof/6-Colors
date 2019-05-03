//---- include section ------
#include "Button.h"
#include "SoundManager.h"

GUI::Button::Button(sf::RenderWindow& window, const string& text)
	: TextView(window, text)
{
	initComponents();
}

string GUI::Button::toString() const
{
	return "Button: { " + TextView::toString() + " }";
}

void GUI::Button::initComponents()
{
	// init sounds at events
	addEnterListener([](View &view) {
		SoundManager::getInterface().playSound("bt_hover");
	});
	addClickListener([](View &view) {
		SoundManager::getInterface().playSound("bt_click");
	});
}
