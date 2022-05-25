#pragma once
#include <SFML/Graphics.hpp>
#include <ranges>
#include <vector>
#include <string>
#include <functional>
#include "Cell.h"
#include "Difficult.h"
#include "IDrawable.h"

class GridController
{
private:
	sf::RenderWindow* window;
	sf::RenderStates* renderStates;
	sf::Text* winText;

	Cell* matrix[9][9]; 

	int hintCounter = 0;
	
	void Transposion(); 
	void SwapRowsSmall(); 
	void SwapColumsSmall(); 
	void SwapRowsArea(); 
	void SwapColumsArea(); 

public:
	Difficult difficultGame; 

	GridController(sf::RenderWindow* _window, sf::RenderStates* _renderStates, sf::Text* _winText); 
	
	void ProcessEvent(sf::Event event); 

	void CheckWin(); 

	void Mix(); 

	void ChangeDifficult(); 

	void Hint();

	void SaveResult();
};

