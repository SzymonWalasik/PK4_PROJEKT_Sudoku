#include "Initilize.h"

	void Initialize::LoadFont(sf::Font& font)
	{
		if (font.loadFromFile(fontPath + fontNameBold)) {
			std::cout << "Loaded Font successful!" << std::endl;
		}
	}

	void Initialize::SetWinText(const sf::Font& font, sf::Text* winText)
	{
		winText->setFont(font);
		winText->setFillColor(sf::Color::Black);
		winText->setCharacterSize(46);
		winText->setString("SUDOKU");
		winText->setPosition(sf::Vector2f(800, 50));
	}

	Button* Initialize::DrawDifficultyButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC, vector<IDrawable*> & objectsToDraw)
	{
		Button* difficultyButton = new Button(window, renderStates, "Easy", sf::Vector2f(1000, 560), sf::Vector2f(200, 64));
		difficultyButton->Click += bind(&GridController::ChangeDifficult, gridC);
		objectsToDraw.push_back(difficultyButton);
		return difficultyButton;
	}

	Button* Initialize::DrawMixButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC, vector<IDrawable*> & objectsToDraw)
	{
		Button* mixButton = new Button(window, renderStates, "Mix", sf::Vector2f(1000, 490), sf::Vector2f(200, 64));
		mixButton->Click += bind(&GridController::Mix, gridC);
		objectsToDraw.push_back(mixButton);
		return mixButton;
	}
	Button* Initialize::DrawHintButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC, vector<IDrawable*>& objectsToDraw)
	{
		Button* hintButton = new Button(window, renderStates, "Hint", sf::Vector2f(1000, 420), sf::Vector2f(200, 64));
		hintButton->Click += bind(&GridController::Hint, gridC);
		objectsToDraw.push_back(hintButton);
		return hintButton;
	}

	void Initialize::SetsOutline(sf::RectangleShape & line1, sf::RectangleShape & line2, sf::RectangleShape & line3, sf::RectangleShape & line4)
	{
		line1.setPosition(upperLeftCornerX, 3 * 64 + upperLeftCornerY - 2);
		line2.setPosition(upperLeftCornerX, 6 * 64 + upperLeftCornerY - 2);
		line3.setPosition(3 * 64 + upperLeftCornerX - 2, upperLeftCornerY);
		line4.setPosition(6 * 64 + upperLeftCornerX - 2, upperLeftCornerY);
		line1.setFillColor(sf::Color::Black);
		line2.setFillColor(sf::Color::Black);
		line3.setFillColor(sf::Color::Black);
		line4.setFillColor(sf::Color::Black);
	}