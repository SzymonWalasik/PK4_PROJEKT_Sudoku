#pragma once
#include "Action.h"
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include "Collider.h"
#include <string>
#include "Globals.h"

class Button : public IDrawable 
{
private:
	sf::RenderWindow* window;		//wska�nik do okienka
	sf::RenderStates* renderStates; 
	sf::RectangleShape shape;
	sf::Texture texture; 
	sf::Font font; 

	int btnWidth;
	int btnHeight;

public:
	void setBackColor(sf::Color color);
	void setFont(sf::Font& fonts);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f point);
	void drawTo();
	bool isMouseOver();

	Collider collider; 
	Action Click; 
	sf::Text caption;	//napis

	Button(sf::RenderWindow* _window, std::string _caption, sf::Vector2f pos, sf::Vector2f size, sf::RenderStates* _renderStates = nullptr);
	Button(sf::RenderWindow* _window, std::string caption, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);

	void ProcessEvent(sf::Event event); 

	virtual void Draw(); 
};


