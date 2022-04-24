#include <vector>
#include <functional>
#include <time.h>
#include <Windows.h>
#include "Initilize.h"

using namespace std;
using namespace placeholders;

vector<IDrawable*> objectsToDraw;

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Sudoku"); 
	sf::RenderStates* renderStates = new sf::RenderStates(); 

	// set font and window text
	sf::Text* winText = new sf::Text();
	sf::Font font;
	Initialize::LoadFont(font); 
	Initialize::SetWinText(font, winText);

	// set the grid controller 
	// this controlelr draws cells and generate numbers
	GridController* gridC = new GridController(window, renderStates, winText);

	// draws outline
	sf::RectangleShape line1(sf::Vector2f(9 * 64, 4));
	sf::RectangleShape line2(sf::Vector2f(9 * 64, 4));
	sf::RectangleShape line3(sf::Vector2f(4, 9 * 64));
	sf::RectangleShape line4(sf::Vector2f(4, 9 * 64));
	Initialize::SetsOutline(line1, line2, line3, line4);

	// draws buttons
	Button* mixButton = Initialize::DrawMixButton(window, renderStates, gridC, objectsToDraw);
	Button* difficultyButton = Initialize::DrawDifficultyButton(window, renderStates, gridC, objectsToDraw);
	

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