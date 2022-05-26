#include "Menu.h"

extern std::vector<IDrawable*> objectsToDraw;

template <typename T>
std::string toString(T arg)
{
	std::stringstream ss;
	ss << arg;
	return ss.str();
}

Menu::Menu():
	MenuState(0)
{};


void Menu::init() {

	int points = 0;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Sudoku");
	sf::RenderStates* renderStates = new sf::RenderStates(); 
	sf::RenderWindow& refWindow = *window;

	// set font and window text
	sf::Text* winText = new sf::Text();
	sf::Font titleFont;
	Initialize::LoadTitleFont(titleFont);
	Initialize::SetWinText(titleFont, winText);

	// set window icon
	Initialize::SetWindowIcon(window);

	// set font
	sf::Font font;
	Initialize::LoadFont(font);

	sf::View view = window->getView();
	sf::Event event;
	sf::String playerInput;
	sf::Text playerText("",font,24);
	sf::Text login("Player name:",font,24);
	sf::Text fail("",font,22);
	sf::Text press("(Press Enter to confirm)",font,10);
	sf::Text score(("Score: "), font,24);

	playerText.setPosition(275, 125);
	login.setPosition(125, 125);
	score.setPosition(270, 125);
	fail.setPosition(125, 265);
	press.setPosition(260, 165);
	playerText.setFillColor(sf::Color::Blue);
	login.setFillColor(sf::Color::Blue);
	score.setFillColor(sf::Color::Blue);
	fail.setFillColor(sf::Color::Blue);
	press.setFillColor(sf::Color::Blue);

	window->draw(login);
	window->draw(press);

	while (window->isOpen())
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
					if (((event.text.unicode <= 57 && event.text.unicode >= 48) || (event.text.unicode <= 91 && event.text.unicode >= 65) || (event.text.unicode >= 97 && event.text.unicode <= 122)) && playerInput.getSize() < 12)
					{
						playerInput += event.text.unicode;
						playerText.setString(playerInput);
					}
				}
				else if (event.type == sf::Event::Closed) {
					window->close();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
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
				if ((std::regex_match(t, std::regex("[A-Za-z0-9]{4,12}"))) || t.empty()) {
					MenuState = 1;
					fail.setString("");
				}
				else {
					fail.setString("Wrong login! Introduce it one more time!");
					window->clear(sf::Color::White);
					window->draw(login);
					window->draw(press);
					window->draw(playerText);
					window->draw(fail);
				}
			}
			else {
				window->clear(sf::Color::White);
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
			Button play(window, "Play", sf::Vector2f(220, 300), sf::Vector2f(200, 64));
			Button scoreTable(window, "Score table", sf::Vector2f(220, 400), sf::Vector2f(200, 64));
			Button exit(window, "Exit", sf::Vector2f(220, 500), sf::Vector2f(200, 64));
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
						MenuState = 3;
					}
					if (scoreTable.isMouseOver()) {
						MenuState = 2;
					}
					if (exit.isMouseOver()) {
						window->close();
					}
				}
				}
				window->clear(sf::Color::White);
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
			//Wyœwietlenie tabeli rekordów globalnej dla guest
			//TODO: Wyœwietlenie tabeli rekordów dla guesta oraz zalogowanego
			//U¿yæ Filesystem + ranges
			break;
		}
		case 3:
		{
			// set the grid controller 
			// this controler draws cells and generate numbers
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
			Button* hintButton = Initialize::DrawHintButton(window, renderStates, gridC, objectsToDraw);
			Button* saveResults = Initialize::DrawSaveResultsButton(window, renderStates, gridC, objectsToDraw);


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
					hintButton->ProcessEvent(event);
					saveResults->ProcessEvent(event);

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

			for (auto o : objectsToDraw)
				delete o;
			objectsToDraw.clear();
			break;
		}
		case 4:
		{
			window->setView(view);
			Button play(window, "Play Again", { 100, 60 }, 16, sf::Color::Color(0, 12, 123), sf::Color::White);
			play.setFont(font);
			play.setPosition({ 134, 450 });
			Button leaderboard(window, "Leaderboard", { 100, 60 }, 16, sf::Color::Color(0, 12, 123), sf::Color::White);
			leaderboard.setFont(font);
			leaderboard.setPosition({ 267, 450 });
			Button exit(window, "Exit", { 100, 60 }, 16, sf::Color::Color(0, 12, 123), sf::Color::White);
			exit.setFont(font);
			exit.setPosition({ 400, 450 });
			while (window->pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window->close();
				}
				case sf::Event::MouseMoved:
				{
					if (play.isMouseOver()) {
						play.setBackColor(sf::Color::Color(255, 201, 14));
						play.setTextColor(sf::Color::Black);
					}
					else {
						play.setBackColor(sf::Color::Color(0, 12, 123));
					}
					if (leaderboard.isMouseOver()) {
						leaderboard.setBackColor(sf::Color::Color(255, 201, 14));
						leaderboard.setTextColor(sf::Color::Black);
					}
					else {
						leaderboard.setBackColor(sf::Color::Color(0, 12, 123));
					}
					if (exit.isMouseOver()) {
						exit.setBackColor(sf::Color::Color(255, 201, 14));
						exit.setTextColor(sf::Color::Black);
					}
					else {
						exit.setBackColor(sf::Color::Color(0, 12, 123));
					}
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (play.isMouseOver()) {
						MenuState = 3;
					}
					if (leaderboard.isMouseOver()) {
						MenuState = 2;
					}
					if (exit.isMouseOver()) {
						window->close();
					}
				}
				}
				window->clear(sf::Color::White);
				window->draw(score);
				sf::Text result(toString<int>(points), font, 24);
				result.setPosition(355, 325);
				window->draw(result);
				window->draw(fail);
				play.drawTo();
				leaderboard.drawTo();
				exit.drawTo();
				window->display();
			}
			break;
		}
		}
	}
}
