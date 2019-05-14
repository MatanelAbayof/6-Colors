#include "UserPlayer.h"
#include <algorithm>    // std::find


UserPlayer::UserPlayer()
	: PlayerBase(), m_selected(false)
{ }

sf::Color UserPlayer::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");

	// now i didnt selcted
	m_selected = false;
		
	sf::Color selectedColor = getLastColor();
	//setLastColor(selectedColor);
	getRivalPlayer()->onOtherPlayerPlayed(selectedColor);

	return selectedColor;
}


void UserPlayer::connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer)
{
	PlayerBase::connectToGame(gameScreen, rivalPlayer);
	init();
}

void UserPlayer::onOtherPlayerPlayed(const sf::Color& selectedColor)
{
	const std::shared_ptr<ColorPanel>& colorPanel = getGameScreen()->getBottomPanel()->getColorPanel();

	auto forbiddenColors = getForbiddenColors();
	for (auto color : ColorPanel::COLORS) {
		auto it = std::find(forbiddenColors.begin(), forbiddenColors.end(), color);
		if(it != forbiddenColors.end()) {
			colorPanel->getColorButton(color)->disable();
		}
		else {
			colorPanel->getColorButton(color)->enable();
		}
	}
}

string UserPlayer::toString() const
{
	return "UserPlayer: { " + PlayerBase::toString() + " }";
}

void UserPlayer::init()
{
	getGameScreen()->getBottomPanel()->getColorPanel()->addClickColorListener([this](std::shared_ptr<ColorButton> colorBT) {
		setLastColor(colorBT->getColor());
		this->m_selected = true;
	});
}

