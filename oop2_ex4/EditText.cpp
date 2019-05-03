//---- include section ------
#include "EditText.h"
#include "Utilities.h"

GUI::EditText::EditText(sf::RenderWindow& window, const string& text)
	: TextView(window, text), m_recordText(false)
{
	init();
}

string GUI::EditText::toString() const
{
	return "EditText: { recordText=" + std::to_string(m_recordText) + ", " + TextView::toString() + " }";
}

void GUI::EditText::init()
{
	// listen to keyboard
	addKeyDownListener(View::KeyReleaseHandler::Listener([this](sf::Keyboard::Key& keyCode) {
		if (this->m_recordText) {
			if (keyCode == sf::Keyboard::Key::BackSpace) {
				// get current text
				string text = getText();
				if (text.length() > 0) {
					// remove last char
					setText(text.substr(0, text.length() - 1));
				}
			}
			else {
				// append text if key code is '\\w'
				this->appendText(Utilities::keyCodeToString(keyCode));
			}			
		}		
	}));
}
