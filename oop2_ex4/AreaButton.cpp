#include "AreaButton.h"

AreaButton::AreaButton(sf::RenderWindow& window, float areaPercent)
	: TextView(window)
{
	setAreaPercent(areaPercent);
	init();
}

float AreaButton::getAreaPercent() const
{
	return m_areaPercent;
}

void AreaButton::setAreaPercent(float area)
{
	if (area < 0.f || area > 100.f)
		throw std::out_of_range("Area percent " + std::to_string(area) + " cannot be less than zero or bigger from 100");
	m_areaPercent = area;
	setText(getPreText() + std::to_string(getAreaPercent()) + "%");
}

string AreaButton::toString() const
{
	return "AreaButton: { " + TextView::toString() + ", areaPercent: " + std::to_string(m_areaPercent) + " }";
}

void AreaButton::init()
{
	setPreText("Area:\n" );
	setTextSize(37);
}
