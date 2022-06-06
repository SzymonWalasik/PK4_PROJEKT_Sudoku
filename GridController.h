#pragma once
#include <SFML/Graphics.hpp>
#include <ranges>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <filesystem>
#include "Cell.h"
#include "Difficult.h"
#include "IDrawable.h"
#include "Globals.h"
//#include "Player.h"
import Player;

namespace fs = std::filesystem;

class GridController
{
private:
	sf::RenderWindow* window;
	sf::RenderStates* renderStates;
	sf::Text* winText;

	Cell* matrix[9][9];		//macierz sudoku

	int hintCounter = 0;
	int scoreCounter = 0;
	Player _player;
	std::vector<std::pair<int, std::string>> v_scores;
	
	void Transposion(); 
	void SwapRowsSmall(); 
	void SwapColumsSmall(); 
	void SwapRowsArea(); 
	void SwapColumsArea(); 

public:
	Difficult difficultGame = Difficult::Easy;

	bool shouldCloseApp = false;

	GridController(sf::RenderWindow* _window, sf::RenderStates* _renderStates, sf::Text* _winText); 
	
	void ProcessEvent(sf::Event event);		//przetwarza zdarzenia tj. klikniêcie mysz¹ itd.

	void SetPlayer(Player player) { _player = player; }

	void CheckWin(); 

	void Mix(); 

	void ChangeDifficult(); 

	void Hint();

	void ExitGame();

	int GetCorrectlyFilledCells();

	void ShowScores(sf::Text& txt);

	void AddScoresToVector(std::string line);

};

