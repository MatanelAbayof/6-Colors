#include "ColorPanel.h"

const std::array<sf::Color, 6> ColorPanel::COLORS = { sf::Color::Blue, sf::Color::Green,
												      sf::Color::Red, sf::Color::Yellow,
												      sf::Color(82, 67, 170), sf::Color(255, 139, 0) };

ColorPanel::ColorPanel(sf::RenderWindow & window)
	: HorizontalLayout(window)
{
	initComponents(window);
}

string ColorPanel::toString() const
{
	return "ColorPanel: " + HorizontalLayout::toString();
}

void ColorPanel::initComponents(sf::RenderWindow & window)
{
	// set my border & background
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));

	//init color panel
	for (int i = 0; i < COLORS.size(); i++) {
		std::shared_ptr<ColorButton> cb = std::make_shared<ColorButton>(window, COLORS[i]);
		m_colorPanel.push_back(cb);
		addView(cb);
	}
}

void ColorPanel::addClickColorListener(std::function<void(std::shared_ptr<ColorButton>)> onClickCB)
{
	for (auto colorButton : m_colorPanel) {
		colorButton->addClickListener([onClickCB, colorButton](View& view) {
			onClickCB(colorButton);
	});
	}
	
}

const std::shared_ptr<ColorButton>& ColorPanel::getColorButton(const sf::Color& color) const
{
	auto it = std::find_if(m_colorPanel.begin(), m_colorPanel.end(), [&color](std::shared_ptr<ColorButton> colorButton) { 
				return colorButton->getColor() == color;
			});
	if (it == m_colorPanel.end())
		throw std::invalid_argument("the color " + std::to_string(color.toInteger()) + "not exists in panel");
	return *it;
}

