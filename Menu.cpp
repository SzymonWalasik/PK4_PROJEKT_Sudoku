#include "Menu.h"

extern std::vector<IDrawable*> objectsToDraw;

Menu::Menu() :MenuState(0) {};		//ustawiamy MenuState na 0

void Menu::init()	//funkcja obs³uguj¹ca ca³¹ grê
{
	int points = 0;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Sudoku");
	sf::RenderStates* renderStates = new sf::RenderStates();
	sf::RenderWindow& refWindow = *window;

	// ustawiamy czcionkê i tekst
	sf::Text* winText = new sf::Text();
	sf::Font titleFont;
	Initialize::LoadTitleFont(titleFont);
	Initialize::SetWinText(titleFont, winText);

	// ustawiamy GridController
	// rysuje komórki i generuje wartoœci
	GridController* gridC = new GridController(window, renderStates, winText);

	// ustawiamy ikonê
	Initialize::SetWindowIcon(window);

	// ustawiamy czcionkê
	sf::Font font;
	Initialize::LoadFont(font);

	sf::View view = window->getView();
	sf::Event event;
	sf::String playerInput;
	sf::Text playerText("", font, 24);
	sf::Text scoreText("", font, 24);
	sf::Text login("Player name:", font, 24);
	sf::Text fail("", font, 22);
	sf::Text press("(Press Enter to confirm)", font, 10);
	sf::Text score(("Top 10 Scores: "), font, 44);

	playerText.setPosition(275, 425);
	login.setPosition(125, 425);
	score.setPosition(100, 50);
	fail.setPosition(125, 265);
	press.setPosition(260, 465);
	playerText.setFillColor(sf::Color::White);
	login.setFillColor(sf::Color::White);
	score.setFillColor(sf::Color::White);
	fail.setFillColor(sf::Color::White);
	press.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	window->draw(login);
	window->draw(press);
	
	sf::Texture texture;		//ustawianie t³a
	if (!texture.loadFromFile(imagesPath + BackgroundImage))
	{
		std::cerr << ".Error while loading background" << std::endl;
		return;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
	window->draw(sprite);
	window->display();

	// tworzenie guzików
	Button play(window, "Play", sf::Vector2f(120, 400), sf::Vector2f(200, 64));
	Button scoreTable(window, "Score table", sf::Vector2f(120, 500), sf::Vector2f(200, 64));
	Button exit(window, "Exit", sf::Vector2f(120, 600), sf::Vector2f(200, 64));
	Button exitFromScore(window, "Exit", sf::Vector2f(120, 600), sf::Vector2f(200, 64));

	// rysowanie obwodu planszy
	sf::RectangleShape line1(sf::Vector2f(9 * 64, 4));
	sf::RectangleShape line2(sf::Vector2f(9 * 64, 4));
	sf::RectangleShape line3(sf::Vector2f(4, 9 * 64));
	sf::RectangleShape line4(sf::Vector2f(4, 9 * 64));
	Initialize::SetsOutline(line1, line2, line3, line4);

	// rysowanie guzików
	Button* mixButton = Initialize::DrawMixButton(window, renderStates, gridC, objectsToDraw);
	Button* difficultyButton = Initialize::DrawDifficultyButton(window, renderStates, gridC, objectsToDraw);
	Button* hintButton = Initialize::DrawHintButton(window, renderStates, gridC, objectsToDraw);
	Button* exitGame = Initialize::DrawExitGameButton(window, renderStates, gridC, objectsToDraw);
	
	while (window->isOpen())	// obs³uga menu
	{
		switch (MenuState)
		{
		case 0:
		{
			window->setView(view);
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (((event.text.unicode <= 57 && event.text.unicode >= 48) || (event.text.unicode <= 91 && event.text.unicode >= 65) || (event.text.unicode >= 97 && event.text.unicode <= 122)) && playerInput.getSize() < 12)	//sprawdzamy poprawnoœæ wpisanego tekstu z klawiatury
					{
						playerInput += event.text.unicode;
						playerText.setString(playerInput);
					}
				}
				else if (event.type == sf::Event::Closed) {
					window->close();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {	//backspace usuwa wszystkie wprowadzone dotychczas znaki
				if (!playerInput.isEmpty()) {
					std::string t = playerInput.toAnsiString();
					std::string newT = "";
					t.pop_back();
					playerInput = t;
					playerText.setString(playerInput);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				std::string t = playerInput.toAnsiString();
				if ((std::regex_match(t, std::regex("[A-Za-z0-9]{3,12}")))) {	//zastosowanie biblioteki regex- polega na walidacji has³a przy naciœniêciu Enter na podstawie iloœci znaków oraz ogranicza wprowadzane symbole do liter i cyfr
					MenuState = 1;
					fail.setString("");
				}
				else {
					fail.setString("Wrong login! Introduce it one more time!");
					window->clear(sf::Color::Black);
					window->draw(sprite);
					window->draw(login);
					window->draw(press);
					window->draw(playerText);
					window->draw(fail);
				}
			}
			else {
				window->clear(sf::Color::Black);
				window->draw(sprite);
				window->draw(login);
				window->draw(press);
				window->draw(playerText);
				window->draw(fail);
			}
			window->display();

			break;
		}
		case 1:
		{
			window->setView(view);
			while (window->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window->close();
				}
				case sf::Event::MouseButtonPressed:
				{
					if (play.isMouseOver()) {
						MenuState = 2;
					}
					if (scoreTable.isMouseOver()) {
						window->clear(sf::Color::White);
						MenuState = 3;
					}
					if (exit.isMouseOver()) {
						window->close();
					}
				}
				}
				window->draw(sprite);
				window->draw(fail);
				play.drawTo();
				scoreTable.drawTo();
				exit.drawTo();
				window->display();
			}
			break;
		}
		case 2:
		{
				gridC->SetPlayer(Player(playerInput.toAnsiString()));
				while (window->isOpen())
				{
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
						hintButton->ProcessEvent(event);
						exitGame->ProcessEvent(event);

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

						if (gridC->shouldCloseApp)
						{
							window->close();
							break;
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
				}

			for (auto o : objectsToDraw)
				delete o;
			objectsToDraw.clear();

			break;
		}

		case 3:
		{
			window->setView(view);

			while (window->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window->close();
				}
				case sf::Event::MouseButtonPressed:
				{
					if (exit.isMouseOver()) {
						MenuState = 1;
						window->clear(sf::Color::Black);
					}
				}
				}

				window->clear(sf::Color::Black);
				gridC->ShowScores(scoreText);
				window->draw(score);
				window->draw(fail);

				exit.drawTo();
				window->display();
			}
			break;
		}
		}
	}
}
