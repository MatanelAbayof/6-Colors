//---- include section ------
#include "ImageView.h"

GUI::ImageView::ImageView(sf::RenderWindow& window)
	: View(window)
{ }

GUI::ImageTexture& GUI::ImageView::getImage()
{
	return m_image;
}

void GUI::ImageView::draw()
{
	View::draw();

	if(isShow())
		m_image.draw(getWindow());
}

string GUI::ImageView::toString() const
{
	return "ImageView: { image=" + m_image.toString() + ", view=" + View::toString() + " }";
}

void GUI::ImageView::updateComponents()
{
	View::updateComponents();

	m_image.updateBounds(getBound());
}
