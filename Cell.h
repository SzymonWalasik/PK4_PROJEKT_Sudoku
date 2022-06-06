#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "IDrawable.h"
#include "Collider.h"
#include "Globals.h"

class Cell : public IDrawable 
{
private:
	sf::RenderWindow* window;
	sf::RenderStates* renderStates;
	sf::RectangleShape shape;
	sf::Texture texture;
	sf::Text caption;
	sf::Font font;
	int positionX;
	int positionY;

	int userValue; 
	bool isFailed; 
	bool isBlocked; 

public:
	int correctValue; 
	Collider collider; 
	int GetXMatrixPosition();
	int GetYMatrixPosition();
	
	Cell() {}
	Cell(sf::RenderWindow* _window, sf::RenderStates* _renderStates, std::string pathTexture, sf::Vector2f size);

	virtual void Draw();

	void SetPosition(sf::Vector2f newPos); 
	void SetMatrixPosition(int y, int x);
	void SetUserNumber(int value); 
	int GetUserNumber(); 
	void SetFail(bool state); 
	bool IsFail();	//zwraca informacje o poprawnoœci wpisanej wartoœci
	void Lock();	//blokuje komórkê 
	void UnLock();	//odblokowuje komórkê do wpisania wartoœci
	bool IsLock();	//sprawdza czy komórka jest odgórnie wype³niona przez algorytm generacji sudoku
};

