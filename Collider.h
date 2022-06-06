#pragma once
#include <SFML/Graphics.hpp>

class Collider	
{
public:
	sf::Vector2f position;	//wektor dwuwymiarowy
	sf::Vector2f size;

	bool IsPointInside(sf::Vector2f checkPos);	//sprawdza czy kursor jest wewn¹trz obszaru pola
};


