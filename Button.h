#pragma once
#include "Action.h"
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include "Collider.h"
#include <string>
#include <iostream>
#include "Globals.h"

class Button : public IDrawable 
{
private:
	sf::RenderWindow* window; 
	sf::RenderStates* renderStates; 
	sf::RectangleShape shape;
	sf::Texture texture; 
	sf::Font font; 

public:
	Collider collider; 
	Action Click; 
	sf::Text caption; 

	
	Button() {}
	Button(sf::RenderWindow* _window, sf::RenderStates* _renderStates, std::string _caption, sf::Vector2f pos, sf::Vector2f size);

	void ProcessEvent(sf::Event event); 

	virtual void Draw(); 
};


