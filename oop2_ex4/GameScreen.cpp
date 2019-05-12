#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow& window)
	: BSGameScreen(window), m_gameMenu(std::make_shared<GameMenu>(window)),
	m_board(std::make_shared<Board>(window)),
	m_bottomPanel(std::make_shared<BottomPanel>(window))
{
	init();
}

string GameScreen::toString() const
{
	return "GameScreen: { " + BSGameScreen::toString() + " }";
}

void GameScreen::init()
{
	addView(m_gameMenu, sf::FloatRect(0.f, 0.f, 1.f, 0.15f));
	addView(m_board, sf::FloatRect(0.05f, 0.17f, 0.9f, 0.65f));
	addView(m_bottomPanel, sf::FloatRect(0.f, 0.85, 1.f, 0.15f));
}
