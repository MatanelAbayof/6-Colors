#include "PolygonView.h"

PolygonView::PolygonView(sf::RenderWindow& window, std::unique_ptr<PolygonShape> polygon)
	: View(window), m_polygon(std::move(polygon))
{
	updatePolygonShape();
	m_polygonDrawable.setOutlineColor(sf::Color::Black);
	m_polygonDrawable.setOutlineThickness(1.f);
}

void PolygonView::addPoint(const sf::Vector2f& relPoint)
{
	m_polygon->addPoint(relPoint);
	updatePolygonShape();
}

void PolygonView::setColor(const sf::Color& color)
{
	m_polygon->setColor(color);
	m_polygonDrawable.setFillColor(m_polygon->getColor()); // update color
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
	return "PolygonView: { color=" + std::to_string(getColor().toInteger()) + ", PolygonShape=" + 
		   m_polygon->toString() + " " + View::toString() + " }";
}

void PolygonView::updateComponents()
{
	View::updateComponents();
	updatePolygonShape();
}

void PolygonView::updatePolygonShape()
{
	m_polygonDrawable.setFillColor(m_polygon->getColor()); // update color

	// update points
	m_polygonDrawable.setPointCount(m_polygon->getNumOfPoints());
	for (size_t i = 0; i < m_polygonDrawable.getPointCount(); ++i) {
		const sf::Vector2f& relPoint = m_polygon->getPoint(static_cast<int>(i));
		sf::Vector2f point;
		point.x = getPosition().x + relPoint.x*float(getSize().x);
		point.y = getPosition().y + relPoint.y*float(getSize().y);
		m_polygonDrawable.setPoint(i, point);
	}
}
