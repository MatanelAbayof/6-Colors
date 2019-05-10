#include "ChooseAIModeScreen.h"




ChooseAIModeScreen::ChooseAIModeScreen(sf::RenderWindow& window)
	: BaseScreen(window),
	m_stupidAIBt(std::make_shared<LevelDifficultyButton>(window)), 
	m_regularAIBt(std::make_shared<LevelDifficultyButton>(window)),
	m_superAIBt(std::make_shared<LevelDifficultyButton>(window))
{
	initComponents();
}

string ChooseAIModeScreen::toString() const
{
	return "ChooseAIModeScreen: { " + BaseScreen::toString() + " }";
}

void ChooseAIModeScreen::initComponents()
{
	// init button
	m_stupidAIBt->setLevel(LevelDifficultyButton::LevelDifficulty::STUPID);
	m_regularAIBt->setLevel(LevelDifficultyButton::LevelDifficulty::REGULAR);
	m_superAIBt->setLevel(LevelDifficultyButton::LevelDifficulty::SUPER);

	addView(m_stupidAIBt, sf::FloatRect(0.35f, 0.15f, 0.3f, 0.15f));
	addView(m_regularAIBt, sf::FloatRect(0.35f, 0.40f, 0.3f, 0.15f));
	addView(m_superAIBt, sf::FloatRect(0.35f, 0.65f, 0.3f, 0.15f));
}
