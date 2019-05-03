//---- include section ------
#include "TextureManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <exception>
#include "LoadResourceException.h"

//---- using section --------
using Json = nlohmann::json;

GUI::TextureManager& GUI::TextureManager::getInterface()
{
	static TextureManager textureManager;
	return textureManager;
}

const GUI::TextureInfo& GUI::TextureManager::getTextureInfo(const string& name)
{
	// check if have this texture
	auto it = m_textures.find(name);
	if (it == m_textures.end())
		throw LoadResourceException("Cannot find the texture with name=" + name);
	return it->second;
}

string GUI::TextureManager::toString() const
{
	string texturesStr = "TextureManager: { Textures={ ";
	int count = 0;
	for (auto it = m_textures.cbegin(); it != m_textures.cend(); ++it) {
		texturesStr += "{ name=" + it->first + ", " + it->second.toString()  + " }";
		if (count + 1 < static_cast<int>(m_textures.size()))
			texturesStr += ", ";
		count++;
	}
	texturesStr += " } " + ResourceLoader::toString() + " }";
	return texturesStr;
}

GUI::TextureManager::TextureManager()
{
	loadTextures();
}

void GUI::TextureManager::loadTextures()
{
	// sounds directory
	string texturesDir = "textures";
	// open JSON file
	string jsonFilePath = texturesDir + "/textures.json";
	std::ifstream jsonFile(jsonFilePath);
	if (!jsonFile.is_open())
		throw LoadResourceException("Cannot open file " + jsonFilePath);
	// try parse JSON
	try {
		// load textures info from JSON to map
		Json texturesJson;
		jsonFile >> texturesJson;

		// parse JSON to textures map
		Json& jsonTexturesObj = texturesJson["textures"];
		// iterate the textures array
		for (Json::iterator it = jsonTexturesObj.begin(); it != jsonTexturesObj.end(); ++it) {
			// get texture info
			Json& jsonTexrureObj = *it;
			// add texture info to map
			string name = jsonTexrureObj["name"].get<string>();
			m_textures[name] = TextureInfo();
			// add texture info data
			TextureInfo& textureInfo = m_textures[name];
			string path = jsonTexrureObj["path"].get<string>();
			string texturePath = texturesDir + "/" + path;
			textureInfo.loadTextureFromFile(texturePath);
			if (jsonTexrureObj["numOfRows"].is_null())
				textureInfo.setNumOfRows(1);
			else
				textureInfo.setNumOfRows(jsonTexrureObj["numOfRows"].get<int>());
			if(jsonTexrureObj["numOfCols"].is_null())
				textureInfo.setNumOfCols(1);
			else
				textureInfo.setNumOfCols(jsonTexrureObj["numOfCols"].get<int>());
			if (jsonTexrureObj["numOfImages"].is_null())
				textureInfo.setNumOfImages(1);
			else
				textureInfo.setNumOfImages(jsonTexrureObj["numOfImages"].get<int>());
		}
	}
	catch (const nlohmann::detail::parse_error& ex) { // error when parse JSON
		throw LoadResourceException("Cannot parse the JSON file " + jsonFilePath + ", the error: " + ex.what());
	}
}
