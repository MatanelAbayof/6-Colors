//---- include section ------
#include "FontManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <exception>
#include "LoadResourceException.h"

//---- using section --------
using Json = nlohmann::json;

GUI::FontManager& GUI::FontManager::getInterface()
{
	static FontManager fontManager;
	return fontManager;
}

const sf::Font& GUI::FontManager::getFont(const string& name)
{
	// check if have this sound
	auto it = m_fonts.find(name);
	if (it == m_fonts.end())
		throw LoadResourceException("Cannot find font with name=" + name);
	return it->second;
}

string GUI::FontManager::toString() const
{
	string str = "FontManager: { names={ ";
	int count = 0;
	for (auto it = m_fonts.cbegin(); it != m_fonts.cend(); ++it) {
		str += it->first;
		if (count + 1 < static_cast<int>(m_fonts.size()))
			str += ", ";
		count++;
	}
	str += " } " + ResourceLoader::toString() + " }";
	return str;
}

GUI::FontManager::FontManager()
{
	loadFonts();
}

void GUI::FontManager::loadFonts()
{
	// fonts directory
	string fontsDir = "fonts";
	// open JSON file
	string jsonFilePath = fontsDir + "/fonts.json";
	std::ifstream jsonFile(jsonFilePath);
	if (!jsonFile.is_open())
		throw LoadResourceException("Cannot open file " + jsonFilePath);

	// try parse JSON
	try {
		// load fonts from JSON to map
		Json fontsJson;
		jsonFile >> fontsJson;

		// parse JSON to fonts map
		Json& jsonFontsObj = fontsJson["fonts"];
		// iterate the fonts array
		for (Json::const_iterator it = jsonFontsObj.cbegin(); it != jsonFontsObj.cend(); ++it) {
			// get font info
			const Json& jsonFontObj = *it;
			string name = jsonFontObj["name"].get<string>();
			string path = jsonFontObj["path"].get<string>();
			// add font to map
			m_fonts[name] = sf::Font();
			string fontPath = fontsDir + "/" + path;
			if (!m_fonts[name].loadFromFile(fontPath))
				throw LoadResourceException("Cannot load font from path " + fontPath);
		}
	}
	catch (const nlohmann::detail::parse_error& ex) { // error when parse JSON
		throw LoadResourceException("Cannot parse the JSON file " + jsonFilePath + ", the error: " + ex.what());
	}
}
