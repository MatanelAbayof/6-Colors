#include "PolygonView.h"

PolygonView::PolygonView(sf::RenderWindow& window, const sf::Color& color)
	: View(window)
{
	setColor(color);
}

void PolygonView::addPoint(const sf::Vector2f& relPoint)
{
	m_polygon.addPoint(relPoint);
	updateComponents();
}

void PolygonView::setColor(const sf::Color& color)
{
	m_polygon.setColor(color);
	m_polygonDrawable.setFillColor(color);
}

void PolygonView::draw()
{
	View::draw();

	if (isShow()) {
		getWindow().draw(m_polygonDrawable);
	}
}

inline string PolygonView::toString() const
{
	return "PolygonShape: { color=" + std::to_string(getColor().toInteger()) + ", numOfPoints=" + 
		   std::to_string(m_polygon.getNumOfPoints()) + " " + View::toString() + " }";
}

void PolygonView::updateComponents()
{
	View::updateComponents();
	updatePolygonShape();
}

void PolygonView::updatePolygonShape()
{
	m_polygonDrawable.setPointCount(m_polygon.getNumOfPoints());
	for (size_t i = 0; i < m_polygonDrawable.getPointCount(); i++) {
		const sf::Vector2f& relPoint = m_polygon.getPoint(i);
		sf::Vector2f point;
		point.x = getPosition().x + relPoint.x*float(getSize().x);
		point.y = getPosition().y + relPoint.y*float(getSize().y);
		m_polygonDrawable.setPoint(i, point);
	}
}
