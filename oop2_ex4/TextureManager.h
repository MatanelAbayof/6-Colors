#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "TextureInfo.h"
#include "ResourceLoader.h"

//---- using section --------
using std::string;

namespace GUI {
/*
 * TextureManager class.
 * this is Singleton design pattern
 */
class TextureManager : public GUI::ResourceLoader
{
public:
	// get interface
	static TextureManager& getInterface();
	// get texture info
	const TextureInfo& getTextureInfo(const string& name);
	// convert to string
	virtual string toString() const override;
private:
	// textures map
	std::unordered_map<string, TextureInfo> m_textures;
	// constructor
	TextureManager();
	// load textures from files
	void loadTextures();
	// disable copy
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(const TextureManager&) = delete;
};
}
