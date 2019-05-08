#pragma once
//---- include section ------
#include <string>
#include <array>
#include <vector>
#include "HorizontalLayout.h"
#include "ColorButton.h"

//---- using section --------
using std::string;

/*
 * ColorPanel class
 */
class ColorPanel :
	public GUI::HorizontalLayout<ColorButton>
{
public:
	// buttons background colors
	static const sf::Color BLUE_COLOR, BLUE_DARK_COLOR, GREEN_COLOR, GREEN_DARK_COLOR, RED_COLOR, RED_DARK_COLOR,
		                   YELLOW_COLOR, YELLOW_DARK_COLOR, PURPLE_COLOR, PURPLE_DARK_COLOR, ORANGE_COLOR, ORANGE_DARK_COLOR;
	// constructor
	explicit ColorPanel(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const override;
	// get button by color
	const std::shared_ptr<ColorButton>& getColorButton(const sf::Color& color) const;
	// add click on color listener
	void addClickColorListener(std::function<void(std::shared_ptr<ColorButton>)> onClickCB);
	// array of colors
	static const std::array<sf::Color, 6> COLORS;
protected:
	//init
	void initComponents(sf::RenderWindow& window);
private:
	//color panel
	std::vector<std::shared_ptr<ColorButton>> m_colorPanel;
};


