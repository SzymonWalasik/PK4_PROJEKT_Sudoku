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
#include "Player.h"

namespace fs = std::filesystem;

class GridController
{
private:
	sf::RenderWindow* window;
	sf::RenderStates* renderStates;
	sf::Text* winText;

	Cell* matrix[9][9]; 

	int hintCounter = 0;
	int scoreCounter = 0;
	Player _player;
	
	void Transposion(); 
	void SwapRowsSmall(); 
	void SwapColumsSmall(); 
	void SwapRowsArea(); 
	void SwapColumsArea(); 

public:
	Difficult difficultGame = Difficult::Easy;

	bool shouldCloseApp = false;

	GridController(sf::RenderWindow* _window, sf::RenderStates* _renderStates, sf::Text* _winText); 
	
	void ProcessEvent(sf::Event event); 

	void SetPlayer(Player player) { _player = player; }

	void CheckWin(); 

	void Mix(); 

	void ChangeDifficult(); 

	void Hint();

	void ExitGame();

	int GetCorrectlyFilledCells();
};

