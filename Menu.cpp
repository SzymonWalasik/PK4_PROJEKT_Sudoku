#include "Menu.h"

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
							if (((event.text.unicode <= 57&& event.text.unicode >=48)||(event.text.unicode <=91&& event.text.unicode >= 65)||( event.text.unicode >=97 && event.text.unicode <=122))&&playerInput.getSize()<12)
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
						if ((std::regex_match(t, std::regex("[A-Za-z0-9]{4,12}")))||t.empty()) {
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
				Button play("Play", { 200, 80 }, 30, sf::Color::Color(0,12,123), sf::Color::White);
				play.setFont(font);
				play.setPosition({ 220, 300 });
				Button leaderboard("Leaderboard", { 200, 80 }, 30, sf::Color::Color(0, 12, 123), sf::Color::White);
				leaderboard.setFont(font);
				leaderboard.setPosition({ 220, 400 });
				Button exit("Exit", { 200, 80 }, 30, sf::Color::Color(0, 12, 123), sf::Color::White);
				exit.setFont(font);
				exit.setPosition({ 220, 500 });
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
							if (play.isMouseOver(refWindow)) {
								play.setBackColor(sf::Color::Color(255, 201, 14));
								play.setTextColor(sf::Color::Black);
							}
							else {
								play.setBackColor(sf::Color::Color(0, 12, 123));
							}
							if (leaderboard.isMouseOver(refWindow)) {
								leaderboard.setBackColor(sf::Color::Color(255, 201, 14));
								leaderboard.setTextColor(sf::Color::Black);
							}
							else {
								leaderboard.setBackColor(sf::Color::Color(0, 12, 123));
							}
							if (exit.isMouseOver(refWindow)) {
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
							if (play.isMouseOver(refWindow)) {
								MenuState = 3;
							}
							if (leaderboard.isMouseOver(refWindow)) {
								MenuState = 2;
							}
							if (exit.isMouseOver(refWindow)) {
								window->close();
							}
						}
					}
					window->clear(sf::Color::White);
					window->draw(fail);
					play.drawTo(refWindow);
					leaderboard.drawTo(refWindow);
					exit.drawTo(refWindow);
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
				//Gra
				//Game* game = new Game(window);
				//points=game->init();
				MenuState = 4;
				std::cout << points << std::endl;
				break;
			}
			case 4:
			{
				window->setView(view);
				//sprite.setTexture(texture);
				//sprite.setPosition(0, 0);
				Button play("Play Again", { 100, 60 }, 16, sf::Color::Color(0, 12, 123), sf::Color::White);
				play.setFont(font);
				play.setPosition({ 134, 450 });
				Button leaderboard("Leaderboard", { 100, 60 }, 16, sf::Color::Color(0, 12, 123), sf::Color::White);
				leaderboard.setFont(font);
				leaderboard.setPosition({ 267, 450 });
				Button exit("Exit", { 100, 60 }, 16, sf::Color::Color(0, 12, 123), sf::Color::White);
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
							if (play.isMouseOver(refWindow)) {
								play.setBackColor(sf::Color::Color(255, 201, 14));
								play.setTextColor(sf::Color::Black);
							}
							else {
								play.setBackColor(sf::Color::Color(0, 12, 123));
							}
							if (leaderboard.isMouseOver(refWindow)) {
								leaderboard.setBackColor(sf::Color::Color(255, 201, 14));
								leaderboard.setTextColor(sf::Color::Black);
							}
							else {
								leaderboard.setBackColor(sf::Color::Color(0, 12, 123));
							}
							if (exit.isMouseOver(refWindow)) {
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
							if (play.isMouseOver(refWindow)) {
								MenuState = 3;
							}
							if (leaderboard.isMouseOver(refWindow)) {
								MenuState = 2;
							}
							if (exit.isMouseOver(refWindow)) {
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
					play.drawTo(refWindow);
					leaderboard.drawTo(refWindow);
					exit.drawTo(refWindow);
					window->display();
				}
				break;
			}
		}
	}

}

