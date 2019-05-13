#include "LevelDifficultyButton.h"


LevelDifficultyButton::LevelDifficultyButton(sf::RenderWindow& window, const string& text)
	:ImageButton(window, text)
{
	init();
}

string LevelDifficultyButton::toString() const
{
	return "LevelDifficultyButton: { " + ImageButton::toString() + " }";
}

void LevelDifficultyButton::setLevelButton(LevelDifficulty levelDiff)
{
	switch (levelDiff) {
		case STUPID: {
			setText("Easy");
			getImage().setTexture("easy");
			getBackground().setColor(sf::Color::Green);
			addLeaveListener(([this](View& view) {
				view.getBackground().setColor(sf::Color(sf::Color::Green));
			}));
		} break;
		case REGULAR: {
			setText("Regular");
			getImage().setTexture("regular");
			getBackground().setColor(sf::Color(255, 139, 0));
			addLeaveListener(([this](View& view) {
				view.getBackground().setColor(sf::Color(sf::Color(255, 139, 0)));
			}));
		} break;
		case SUPER: {
			setText("Difficult");
			getImage().setTexture("super");
			getBackground().setColor(sf::Color::Red);
			addLeaveListener(([this](View& view) {
				view.getBackground().setColor(sf::Color(sf::Color::Red));
			}));
		} break;
	}
	m_levelDiff = levelDiff;
}

void LevelDifficultyButton::init()
{
	setTextColor(sf::Color::Black);
	setFont("CURLZ");
	setTextSize(30);
	addEnterListener([this](View& view) {
		view.getBackground().setColor(sf::Color(255, 255, 255, 128));
	});
}

