#pragma once
//---- include section ------
#include <SFML/Graphics.hpp>
#include <string>

//---- using section --------
using std::string;

namespace GUI {
/*
 * TextureInfo class
 */
class TextureInfo
{
public:
	// constructor
	TextureInfo();
	// set number of rows
	void setNumOfRows(int numOfRows);
	// get number of rows
	int getNumOfRows() const;
	// set number of columns
	void setNumOfCols(int numOfCols);
	// get number of columns
	int getNumOfCols() const;
	// set number of images
	void setNumOfImages(int numOfImages);
	// get number of images
	int getNumOfImages() const;
	// load texture from file
	void loadTextureFromFile(const string& filePath);
	// get texture
	const sf::Texture& getTexture() const;
	// convert to string
	string toString() const;
private:
	// texture
	sf::Texture m_texture;
	// number of rows and columns that texture splitted
	int m_numOfRows, m_numOfCols;
	// numbers of images in texture
	int m_numOfImages;
};
}
