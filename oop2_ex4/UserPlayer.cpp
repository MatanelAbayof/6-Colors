#include "UserPlayer.h"
#include <algorithm>    // std::find


UserPlayer::UserPlayer()
	: PlayerBase(), m_selected(false)
{
	setName("User");
}

sf::Color UserPlayer::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");		
	sf::Color selectedColor = getLastColor();
	//setLastColor(selectedColor);
	getRivalPlayer()->onOtherPlayerPlayed(selectedColor);
	onPlayerPlayed(selectedColor);
	return selectedColor;
}


void UserPlayer::connectToGame(GameScreen* gameScreen, const std::shared_ptr<PlayerBase>& rivalPlayer)
{
	PlayerBase::connectToGame(gameScreen, rivalPlayer);
	init();
}

void UserPlayer::onOtherPlayerPlayed(const sf::Color& selectedColor)
{
	updateForbiddenColors();
}

void UserPlayer::onPlayerPlayed(const sf::Color& selectedColor)
{
	m_selected = false;
	updateForbiddenColors();
}

void UserPlayer::setStartVertex(GraphVertex vertex)
{
	PlayerBase::setStartVertex(vertex);
	updateForbiddenColors();
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

void UserPlayer::updateForbiddenColors()
{
	const std::shared_ptr<ColorPanel>& colorPanel = getGameScreen()->getBottomPanel()->getColorPanel();
	std::vector<sf::Color> forbiddenColors = getForbiddenColors();
	for (const sf::Color& color : ColorPanel::COLORS) {
		auto it = std::find(forbiddenColors.begin(), forbiddenColors.end(), color);
		if (it != forbiddenColors.end())
			colorPanel->getColorButton(color)->disable();
		else
			colorPanel->getColorButton(color)->enable();
	}
}

