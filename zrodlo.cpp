#include <vector>
#include <functional>
#include <time.h>
#include <Windows.h>
#include <ranges>
#include <SFML/Graphics.hpp>
#include "GridController.h"
#include "Button.h"
#include "Difficult.h"
#include "IDrawable.h"
#include "Globals.h"

using namespace std;
using namespace placeholders;

vector<IDrawable*> objectsToDraw;

void LoadFont(sf::Font & font)
{
	if (font.loadFromFile(fontPath + fontNameBold)) {
		std::cout << "Loaded Font successful!" << std::endl;
	}
}

void SetWinText(const sf::Font& font, sf::Text* winText)
{
	winText->setFont(font);
	winText->setFillColor(sf::Color::Black);
	winText->setCharacterSize(46);
	winText->setString("SUDOKU");
	winText->setPosition(sf::Vector2f(800, 50));
}

void DrawsAndDisplayObjectsToDraw(sf::Window)
{

}
Button* DrawDifficultyButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC)
{
	Button* difficultyButton = new Button(window, renderStates, "Easy", sf::Vector2f(1000, 560), sf::Vector2f(200, 64));
	difficultyButton->Click += bind(&GridController::ChangeDifficult, gridC);
	objectsToDraw.push_back(difficultyButton);
	return difficultyButton;
}

Button* DrawMixButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC)
{
	Button* mixButton = new Button(window, renderStates, "Mix", sf::Vector2f(1000, 490), sf::Vector2f(200, 64));
	mixButton->Click += bind(&GridController::Mix, gridC);
	objectsToDraw.push_back(mixButton);
	return mixButton;
}

void SetsOutline(sf::RectangleShape line1, sf::RectangleShape line2, sf::RectangleShape line3, sf::RectangleShape line4)
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


int main()
{
	//srand(time(0)); 
	//FreeConsole();

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Sudoku"); 
	sf::RenderStates* renderStates = new sf::RenderStates(); 

	// set font and window text
	sf::Text* winText = new sf::Text();
	sf::Font font;
	LoadFont(font); 
	SetWinText(font, winText);

	// set the grid controller 
	// this controlelr draws cells and generate numbers
	GridController* gridC = new GridController(window, renderStates, winText);

	// draws outline
	sf::RectangleShape line1(sf::Vector2f(9 * 64, 4));
	sf::RectangleShape line2(sf::Vector2f(9 * 64, 4));
	sf::RectangleShape line3(sf::Vector2f(4, 9 * 64));
	sf::RectangleShape line4(sf::Vector2f(4, 9 * 64));
	SetsOutline(line1, line2, line3, line4);

	// draws buttons
	Button* mixButton = DrawMixButton(window, renderStates, gridC);
	Button* difficultyButton = DrawDifficultyButton(window, renderStates, gridC);
	

	while (window->isOpen()) 
	{
		sf::Event event; 
		while (window->pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
				window->close(); 

			if (event.type == sf::Event::Resized) 
			{
				sf::FloatRect visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height); 
				window->setView(sf::View(visibleArea)); 
				
				renderStates->transform = sf::Transform((float)(event.size.width) / 1280, 0, 0, 0, (float)(event.size.width) / 1280, 0, 0, 0, 1);
			}

			gridC->ProcessEvent(event); 
			mixButton->ProcessEvent(event); 
			difficultyButton->ProcessEvent(event); 

			switch (gridC->difficultGame) 
			{
			case Difficult::Easy: 
				difficultyButton->caption.setString("Easy");
				break;
			case Difficult::Normal:
				difficultyButton->caption.setString("Normal");
				break;
			case Difficult::Hard:
				difficultyButton->caption.setString("Hard");
				break;
			}
		}

		window->clear(sf::Color::White);

		for (auto o : objectsToDraw)
			o->Draw(); 
		window->draw(line1, *renderStates); 
		window->draw(line2, *renderStates);
		window->draw(line3, *renderStates);
		window->draw(line4, *renderStates);

		window->draw(*winText, *renderStates); 

		window->display(); 
	}

	
	delete window;
	delete renderStates;
	for (auto o : objectsToDraw)
		delete o;
	objectsToDraw.clear();

	return 0; 
}