#pragma once
//---- include section ------
#include <string>
#include "HorizontalLayout.h"
#include "View.h"
#include "ColorPanel.h"
#include "AreaButton.h"

//---- using section --------
using std::string;

/*
 * BottomPanel class
 */
class BottomPanel :
	public GUI::HorizontalLayout<GUI::View>
{
public:
	// constructor
	explicit BottomPanel(sf::RenderWindow& window);
	// get color panel
	const std::shared_ptr<ColorPanel>& getColorPanel() const { return m_colorPanel; }
	//get my arae button
	std::shared_ptr<AreaButton>& getMyAreaButton() { return m_myArea; }
	//get rival arae button
	std::shared_ptr<AreaButton>& getRivalAreaButton() { return m_rivalArea; }
	// convert to string
	virtual string toString() const override;
protected:
	//init
	void initComponents(sf::RenderWindow& window);
	//init button
	void initButton(const std::shared_ptr<AreaButton>& bt);
	//init color panel bootom
	void initColorPanel(const std::shared_ptr<ColorPanel>& bt);
private:
	//color panel
	std::shared_ptr<ColorPanel> m_colorPanel;
	//the area button
	std::shared_ptr<AreaButton> m_myArea, m_rivalArea;
};

