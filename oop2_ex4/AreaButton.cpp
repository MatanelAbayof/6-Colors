#include "AreaButton.h"


AreaButton::AreaButton(sf::RenderWindow& window, const string& text, float areaPercent)
	: TextView(window, text)
{
	setAreaPercent(areaPercent);
	setText("Area:\n" + std::to_string(getAreaPercent()) + "%");
	setTextSize(40);
}

float& AreaButton::getAreaPercent()
{
	return m_areaPercent;
}

void AreaButton::setAreaPercent(float area)
{
	if (area < 0)
		throw std::out_of_range("Area percent " + std::to_string(area) + " cannot be less than zero");
	m_areaPercent = area;
}

string AreaButton::toString() const
{
	return "AreaButton: { " + TextView::toString() + ", areaPercent: " + std::to_string(m_areaPercent) + " }";
}
