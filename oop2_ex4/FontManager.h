#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "ResourceLoader.h"

//---- using section --------
using std::string;

namespace GUI {
/*
 * FontManager class.
 * this is Singleton design pattern
 */
class FontManager : public GUI::ResourceLoader
{
public:
	// get interface
	static FontManager& getInterface();
	// get font by name
	const sf::Font& getFont(const string& name);
	// convert to string
	virtual string toString() const override;
private:
	// fonts
	std::unordered_map<string, sf::Font> m_fonts;
	// constructor
	FontManager();
	// disable copy
	FontManager& operator=(const FontManager&) = delete;
	FontManager(const FontManager&) = delete;
	// load fonts
	void loadFonts();
};
}

