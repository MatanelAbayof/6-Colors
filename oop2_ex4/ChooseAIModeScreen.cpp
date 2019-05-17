#include "ChooseAIModeScreen.h"

ChooseAIModeScreen::ChooseAIModeScreen(sf::RenderWindow& window)
	: BaseScreen(window),
	m_stupidAIBt(std::make_shared<LevelDifficultyButton>(window)), 
	m_regularAIBt(std::make_shared<LevelDifficultyButton>(window)),
	m_superAIBt(std::make_shared<LevelDifficultyButton>(window))
{
	initComponents();
}

void ChooseAIModeScreen::addLevelClickListener(std::function<void(std::shared_ptr<LevelDifficultyButton>)> onClickBT)
{
	m_stupidAIBt->addClickListener([onClickBT, this](View& view) {
		onClickBT(this->m_stupidAIBt);
	});
	m_regularAIBt->addClickListener([onClickBT, this](View& view) {
		onClickBT(this->m_regularAIBt);
	});
	m_superAIBt->addClickListener([onClickBT, this](View& view) {
		onClickBT(this->m_superAIBt);
	});
}

string ChooseAIModeScreen::toString() const
{
	return "ChooseAIModeScreen: { " + BaseScreen::toString() + " }";
}

void ChooseAIModeScreen::initComponents()
{
	// init button
	m_stupidAIBt->setLevelButton(LevelDifficultyButton::LevelDifficulty::STUPID);
	m_regularAIBt->setLevelButton(LevelDifficultyButton::LevelDifficulty::REGULAR);
	m_superAIBt->setLevelButton(LevelDifficultyButton::LevelDifficulty::SUPER);

	addView(m_stupidAIBt, sf::FloatRect(0.35f, 0.15f, 0.3f, 0.15f));
	addView(m_regularAIBt, sf::FloatRect(0.35f, 0.40f, 0.3f, 0.15f));
	addView(m_superAIBt, sf::FloatRect(0.35f, 0.65f, 0.3f, 0.15f));
}
