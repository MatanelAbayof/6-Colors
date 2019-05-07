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
	// constructor
	explicit ColorPanel(sf::RenderWindow& window);
	// convert to string
	virtual string toString() const override;
	// get button by color
	const std::shared_ptr<ColorButton>& getColorButton(const sf::Color& color) const;
	// add click on color listever
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


