//---- include section ------
#include "TextureInfo.h"
#include "LoadResourceException.h"

GUI::TextureInfo::TextureInfo()
	: m_numOfRows(0), m_numOfCols(0), m_numOfImages(0)
{ }

void GUI::TextureInfo::setNumOfRows(int numOfRows)
{
	if (numOfRows < 0)
		throw std::out_of_range("Number of rows must be bigger or equals to zero (=" + std::to_string(numOfRows) + ")");
	m_numOfRows = numOfRows;
}

int GUI::TextureInfo::getNumOfRows() const
{
	return m_numOfRows;
}

void GUI::TextureInfo::setNumOfCols(int numOfCols)
{
	if (numOfCols < 0)
		throw std::out_of_range("Number of columns must be bigger or equals to zero (=" + std::to_string(numOfCols) + ")");
	m_numOfCols = numOfCols;
}

int GUI::TextureInfo::getNumOfCols() const
{
	return m_numOfCols;
}

void GUI::TextureInfo::setNumOfImages(int numOfImages)
{
	if (numOfImages < 0)
		throw std::out_of_range("Number of images must be bigger or equals to zero (=" + std::to_string(numOfImages) + ")");
	m_numOfImages = numOfImages;
}

int GUI::TextureInfo::getNumOfImages() const
{
	return m_numOfImages;
}

void GUI::TextureInfo::loadTextureFromFile(const string& filePath)
{
	if (!m_texture.loadFromFile(filePath))
		throw LoadResourceException("Cannot load texture from file path=" + filePath);
}

const sf::Texture& GUI::TextureInfo::getTexture() const
{
	return m_texture;
}

string GUI::TextureInfo::toString() const
{
	return "TextureInfo: { numOfRows=" + std::to_string(m_numOfRows) + ", numOfCols=" + std::to_string(m_numOfCols) +
			", numOfImages=" + std::to_string(m_numOfImages) + " }";
}
