#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "GridController.h"
#include "Button.h"
#include "Difficult.h"
#include "IDrawable.h"
#include <iostream>

static class Initialize
{
	public:

		static void LoadFont(sf::Font& font);

		static void SetWinText(const sf::Font& font, sf::Text* winText);

		static Button* DrawDifficultyButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC, vector<IDrawable*> & objectsToDraw);

		static Button* DrawMixButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC, vector<IDrawable*> & objectsToDraw);

		static Button* DrawHintButton(sf::RenderWindow* window, sf::RenderStates* renderStates, GridController* gridC, vector<IDrawable*>& objectsToDraw);

		static void SetsOutline(sf::RectangleShape line1, sf::RectangleShape line2, sf::RectangleShape line3, sf::RectangleShape line4);
};
