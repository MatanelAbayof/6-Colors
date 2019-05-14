#include "UserPlayer.h"



UserPlayer::UserPlayer()
	: PlayerBase()
{
}

sf::Color UserPlayer::selectColor()
{
	if (!isReadyToPlay())
		throw std::exception("cannot select color");

	// now i didnt selcted
	m_selected = false;
		
	return m_selectedColor;
}


string UserPlayer::toString() const
{
	return "UserPlayer: {" + PlayerBase::toString() + " }";
}

void UserPlayer::init()
{
	getGameScreen()->getBottomPanel()->getColorPanel()->addClickColorListener([this](std::shared_ptr<ColorButton> colorBT) {
		this->m_selectedColor = colorBT->getColor();
		this->m_selected = true;
	});
}

