//---- include section ------
#include "TextView.h"
#include "Utilities.h"
#include "FontManager.h"

GUI::TextView::TextView(sf::RenderWindow& window, const string& text)
			: View(window), m_textHAlign(CENTER)
{
	// init text object
	setFont("arial"); // default font
	m_text.setCharacterSize(17);
	m_text.setFillColor(sf::Color::Black);
	setText(text);
}

string GUI::TextView::getText() const
{
	return m_text.getString();
}

void GUI::TextView::setText(const string &text)
{
	m_text.setString(text);
	updateComponents();
}

void GUI::TextView::appendText(const string& text)
{
	setText(getText() + text);
}

void GUI::TextView::setTextColor(const sf::Color& textColor)
{
	m_textColor = textColor;
	m_text.setFillColor(m_textColor);
}

sf::Color GUI::TextView::getTextColor() const
{
	return m_textColor;
}

void GUI::TextView::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void GUI::TextView::setFont(const string& fontName)
{
	setFont(FontManager::getInterface().getFont(fontName));
}

void GUI::TextView::setTextHAlignment(TextHAlignment textHAlign)
{
	m_textHAlign = textHAlign;
	updateComponents();
}

void GUI::TextView::setTextSize(unsigned int textSize)
{
	m_text.setCharacterSize(textSize);
	updateComponents();
}

unsigned int GUI::TextView::getTextSize() const
{
	return m_text.getCharacterSize();
}

GUI::TextView::TextHAlignment GUI::TextView::getTextHAlignment() const
{
	return m_textHAlign;
}

void GUI::TextView::setTextStyle(sf::Uint32 style)
{
	m_text.setStyle(style);
}

void GUI::TextView::draw()
{
	View::draw();
	sendDrawRequest(m_text);
}

string GUI::TextView::toString() const
{
	return "TextView: { text=" + m_text.getString() + ", " + View::toString() + " }";
}

void GUI::TextView::updateComponents()
{
	View::updateComponents();

	if (isNoSet())
		return;

	// reset position & scale
	m_text.setPosition(getPosition());
	m_text.setScale(1, 1);

	// resize text (do like this becuse we dont want to 'spread' the text with scaling)
	while (m_text.getGlobalBounds().height > getBound().height) {
		float newScaleY = m_text.getScale().y - 0.1f;
		if (newScaleY < 0)
			break; // No enough space!
		m_text.setScale(m_text.getScale().x, newScaleY);
	}
	while (m_text.getGlobalBounds().width > getBound().width) {
		float newScaleX = m_text.getScale().x - 0.1f;
		if (newScaleX < 0)
			break; // No enough space!
		m_text.setScale(newScaleX, m_text.getScale().y);
	}

	// margin text to center
	float dHeight = getBound().height - m_text.getGlobalBounds().height;
	switch (m_textHAlign)
	{
		case RIGHT: {
			m_text.setPosition(sf::Vector2f(getPosition().x + getBound().width - m_text.getGlobalBounds().width,
				getPosition().y + dHeight / 2));
		} break;
		case LEFT: {
			m_text.setPosition(sf::Vector2f(getPosition().x,
				getPosition().y + dHeight / 2));
		} break;
		case CENTER: {
			float dWidth = getBound().width - m_text.getGlobalBounds().width;
			m_text.setPosition(sf::Vector2f(getPosition().x + dWidth / 2,
				getPosition().y + dHeight / 2));
		} break;
	}
}
