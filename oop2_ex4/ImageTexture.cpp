//---- include section ------
#include "ImageTexture.h"
#include "RectUtils.h"
#include "TextureManager.h"

//---- using section --------
using sf::RectangleShape;

GUI::ImageTexture::ImageTexture()
{ 
	setColor(sf::Color::Transparent);
}

GUI::ImageTexture::ImageTexture(const sf::Color& color)
{
	setColor(color);
}

GUI::ImageTexture::ImageTexture(sf::Texture& texture)
{
	setTexture(texture);
}

GUI::ImageTexture::ImageTexture(const string& textureName)
{
	setTexture(textureName);
}

GUI::ImageTexture::ImageTexture(const ImageTexture& other)
{
	m_bounds = other.m_bounds;
	m_loadMode = other.m_loadMode;
	if (other.m_rectColor)
		m_rectColor = std::make_unique<sf::RectangleShape>(*other.m_rectColor);
	if (other.m_spriteTexture)
		m_spriteTexture = std::make_unique<sf::Sprite>(*other.m_spriteTexture);
}

GUI::ImageTexture::LoadMode GUI::ImageTexture::getLoadMode() const
{
	return m_loadMode;
}

void GUI::ImageTexture::setTexture(const sf::Texture& texture)
{
	// change load mode
	m_loadMode = TEXTURE;
	// create sprite if is null
	if (!m_spriteTexture)
		m_spriteTexture = std::make_unique<sf::Sprite>();
	// set texture
	m_spriteTexture->setTexture(texture);
	updateBounds(m_bounds);
}

void GUI::ImageTexture::setTexture(const string& textureName)
{
	setTexture(TextureManager::getInterface().getTextureInfo(textureName).getTexture());
}

void GUI::ImageTexture::setColor(const sf::Color& color)
{
	// change load mode
	m_loadMode = COLOR;
	// create rectangle if is null
	if (!m_rectColor)
		m_rectColor = std::make_unique<sf::RectangleShape>();
	// set color
	m_rectColor->setFillColor(color);
	updateBounds(m_bounds);
}

void GUI::ImageTexture::updateBounds(const sf::FloatRect& bounds)
{
	switch (m_loadMode)
	{
		case ImageTexture::TEXTURE: {
			if (m_spriteTexture) {
				m_spriteTexture->setPosition(sf::Vector2f(bounds.left, bounds.top));
				sf::Vector2u textureSize = m_spriteTexture->getTexture()->getSize();
				m_spriteTexture->setScale(bounds.width / (float)textureSize.x, bounds.height / (float)textureSize.y);
			}			
		} break;
		case ImageTexture::COLOR: {
			if (m_rectColor) {
				m_rectColor->setPosition(sf::Vector2f(bounds.left, bounds.top));
				m_rectColor->setSize(sf::Vector2f(bounds.width, bounds.height));
			}			
		} break;
	}
	m_bounds = bounds;
}

void GUI::ImageTexture::draw(sf::RenderWindow& window)
{
	switch (m_loadMode)
	{
		case ImageTexture::TEXTURE: {
			if (m_spriteTexture)
				window.draw(*m_spriteTexture);
		} break;
		case ImageTexture::COLOR: {
			if (m_rectColor) {
				if (m_rectColor->getFillColor() != sf::Color::Transparent)
					window.draw(*m_rectColor);
			}		
		} break;
	}
}

string GUI::ImageTexture::toString() const
{
	string loadModeStr = (m_loadMode == COLOR) ? "Color" : "Texture";
	return "ImageTexture: { loadMode=" + loadModeStr + " }";
}
