#include "ColorPanel.h"

const sf::Color ColorPanel::BLUE_COLOR(sf::Color::Blue), ColorPanel::BLUE_DARK_COLOR(sf::Color(0, 0, 153)),
                ColorPanel::GREEN_COLOR(sf::Color::Green), ColorPanel::GREEN_DARK_COLOR(sf::Color(0, 102, 0)),
                ColorPanel::RED_COLOR(sf::Color::Red), ColorPanel::RED_DARK_COLOR(sf::Color(204, 0, 0)),
                ColorPanel::YELLOW_COLOR(sf::Color::Yellow), ColorPanel::YELLOW_DARK_COLOR(sf::Color(255, 204, 0)),
                ColorPanel::PURPLE_COLOR(sf::Color(82, 67, 170)), ColorPanel::PURPLE_DARK_COLOR(sf::Color(102, 0, 102)),
                ColorPanel::ORANGE_COLOR(sf::Color(255, 139, 0)), ColorPanel::ORANGE_DARK_COLOR(sf::Color(255, 153, 0));

// init array
const std::array<sf::Color, 6> ColorPanel::COLORS = { BLUE_COLOR, GREEN_COLOR,
													  RED_COLOR, YELLOW_COLOR,
													  PURPLE_COLOR, ORANGE_COLOR };

ColorPanel::ColorPanel(sf::RenderWindow & window)
	: HorizontalLayout(window)
{
	initComponents(window);
}

string ColorPanel::toString() const
{
	return "ColorPanel: { " + HorizontalLayout::toString() + " }";
}

void ColorPanel::initComponents(sf::RenderWindow & window)
{
	// set my border & background
	getBorder().setColor(sf::Color::Black);
	getBorder().setSize(1.f);
	getBackground().setColor(sf::Color(240, 255, 239));

	//init color panel
	for (size_t i = 0; i < COLORS.size(); i++) {
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
	// check if not found the color
	if (it == m_colorPanel.end())
		throw std::invalid_argument("The color " + std::to_string(color.toInteger()) + "not exists in panel");
	return *it;
}

