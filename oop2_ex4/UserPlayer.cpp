#include "UserPlayer.h"



UserPlayer::UserPlayer()
	: PlayerBase(), m_selected(false)
{ }

sf::Color UserPlayer::selectColor()
{
	if (!isReadyToPlay())
		throw std::logic_error("Cannot select color");

	// now i didnt selcted
	m_selected = false;
		
	return m_selectedColor;
}


void UserPlayer::connectToGame(GameScreen* gameScreen)
{
	PlayerBase::connectToGame(gameScreen);
	init();
}

string UserPlayer::toString() const
{
	return "UserPlayer: { " + PlayerBase::toString() + " }";
}

void UserPlayer::init()
{
	getGameScreen()->getBottomPanel()->getColorPanel()->addClickColorListener([this](std::shared_ptr<ColorButton> colorBT) {
		this->m_selectedColor = colorBT->getColor();
		this->m_selected = true;
	});
}

