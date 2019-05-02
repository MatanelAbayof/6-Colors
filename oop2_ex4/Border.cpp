//---- include section ------
#include "Border.h"

GUI::Border::Border(const sf::Color& color, float size)
{
	setColor(color);
	setSize(size);
}

GUI::Border::Border(const Border& other)
{
	if (other.isRectInit()) // copy rectangle if created in other
		m_rectBorder = std::make_unique<sf::RectangleShape>(*other.m_rectBorder);
	// copy other fields
	m_bounds = other.m_bounds;
	m_color = other.m_color;
	m_size = other.m_size;
}

void GUI::Border::setColor(const sf::Color& color)
{
	m_color = color;
	if (color != sf::Color::Transparent) {
		if (!isRectInit()) // create rectangle if need
			createRectShape();
		m_rectBorder->setOutlineColor(color);
	}
	else {
		if (isRectInit())
			deleteRectShape();
	}
}

void GUI::Border::setSize(float size)
{
	if (size < 0)
		throw std::invalid_argument("Size of border (=" + std::to_string(size) + ") must be a natural number");
	m_size = size;
	if (size > 0) {
		if (!isRectInit()) // create rectangle if need
			createRectShape();
		m_rectBorder->setOutlineThickness(size);
		updateBounds(m_bounds);
	}
	else { // size=0
		if (isRectInit())
			deleteRectShape();
	}		
}

void GUI::Border::updateBounds(const sf::FloatRect& bounds)
{
	m_bounds = bounds;
	if (isRectInit()) {
		m_rectBorder->setPosition(sf::Vector2f(bounds.left + getSize(), bounds.top + getSize()));
		m_rectBorder->setSize(sf::Vector2f(bounds.width - 2 * getSize(), bounds.height - 2 * getSize()));
	}	
}

void GUI::Border::draw(sf::RenderWindow& window)
{	
	if (isRectInit()) {
		sf::FloatRect bounds = m_rectBorder->getGlobalBounds();
		if ((bounds.width > 0) && (bounds.height > 0)) {
			window.draw(*m_rectBorder);
		}
	}
}

string GUI::Border::toString() const
{
	return "Border: { color=" + std::to_string(getColor().toInteger()) + ", size=" + std::to_string(getSize()) + " }";
}

void GUI::Border::createRectShape()
{
	m_rectBorder = std::make_unique<sf::RectangleShape>(); // create rectangle
	m_rectBorder->setFillColor(sf::Color::Transparent); // hide inside color
	// update color and size
	m_rectBorder->setOutlineColor(m_color);
	m_rectBorder->setOutlineThickness(m_size);
	// update bounds
	updateBounds(m_bounds);
}
