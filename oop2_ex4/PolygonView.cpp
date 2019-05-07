#include "PolygonView.h"

PolygonView::PolygonView(sf::RenderWindow& window, const sf::Color& color)
	: View(window)
{
	setColor(color);
}

void PolygonView::addPoint(const sf::Vector2f& relPoint)
{
	if (!isLegalRelPoint(relPoint))
		throw std::invalid_argument("Relative point {x=" + std::to_string(relPoint.x) + ", y=" + std::to_string(relPoint.y) + "} must be in [0, 1]");
	m_relPoints.push_back(relPoint);
	updateComponents();
}

void PolygonView::draw()
{
	View::draw();

	if (isShow()) {
		getWindow().draw(m_polygonShape);
	}
}

inline string PolygonView::toString() const
{
	return "PolygonShape: { color=" + std::to_string(getColor().toInteger()) + ", numOfPoints=" + 
		   std::to_string(m_relPoints.size()) + " " + View::toString() + " }";
}

void PolygonView::updateComponents()
{
	View::updateComponents();
	updatePolygonShape();
}

void PolygonView::updatePolygonShape()
{
	m_polygonShape.setPointCount(m_relPoints.size());
	for (size_t i = 0; i < m_polygonShape.getPointCount(); i++) {
		const sf::Vector2f& relPoint = m_relPoints[i];
		sf::Vector2f point;
		point.x = getPosition().x + relPoint.x*float(getSize().x);
		point.y = getPosition().y + relPoint.y*float(getSize().y);
		m_polygonShape.setPoint(i, point);
	}
}
