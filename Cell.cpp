#include "Cell.h"

Cell::Cell(sf::RenderWindow* _window, sf::RenderStates* _renderStates, std::string pathTexture, sf::Vector2f size)
{
	window = _window;
	renderStates = _renderStates;

	sf::Image image;
	texture = sf::Texture();
	image.loadFromFile(imagesPath + pathTexture);
	texture.loadFromImage(image);

	//texture.loadFromFile("Images/" + pathTexture);

	shape = sf::RectangleShape(size);
	shape.setTexture(&texture);
	shape.setPosition(sf::Vector2f(0, 0));

	if (font.loadFromFile(fontPath+fontName)) {
		std::cout << "Loaded Font successful!" << std::endl;
	}
	caption.setFont(font);
	caption.setFillColor(sf::Color::Black);
	caption.setCharacterSize(25);
	caption.setString("");
	sf::FloatRect b = caption.getGlobalBounds();
	caption.setPosition(shape.getPosition().x + shape.getSize().x / 2 - b.width / 2, shape.getPosition().y + b.height);

	isBlocked = false;
	isFailed = false;
	correctValue = 0;
	userValue = 0;

	collider.position = shape.getPosition();
	collider.size = shape.getSize();
}

void Cell::Draw()
{
	window->draw(shape, *renderStates);
	window->draw(caption, *renderStates);
}

void Cell::SetPosition(sf::Vector2f newPos)
{
	shape.setPosition(newPos); 

	collider.position = shape.getPosition(); 

	
	sf::FloatRect b = caption.getGlobalBounds(); 
	caption.setPosition(shape.getPosition().x + shape.getSize().x / 2 - b.width / 2, shape.getPosition().y + b.height);
}

void Cell::SetMatrixPosition(int y, int x)
{
	positionX = x;
	positionY = y;
}

int Cell::GetXMatrixPosition()
{
	return positionX;
}

int Cell::GetYMatrixPosition()
{
	return positionY;
}

void Cell::SetUserNumber(int value)
{
	if (isBlocked) return; 

	
	if (value > 9) value = 9;
	else if (value < 0) value = 0;

	userValue = value; 
	if (userValue == 0) 
		caption.setString(""); 
	else
		caption.setString(std::to_string(userValue)); 
}

int Cell::GetUserNumber()
{
	return userValue; 
}

void Cell::SetFail(bool state)
{
	if (isBlocked) return; 

	isFailed = state; 
	if (isFailed) {
		caption.setFillColor(sf::Color::Red);		//jesli cyfra wpisana w komorke koliduje z inna cyfra w rzedzie kolumnie lub podtablicy bedzie czerwona
	}
	else
	{
		caption.setFillColor(sf::Color::Blue);		//jesli cyfra nie koliduje z rzadna inna bedzie niebieska
	}
}

bool Cell::IsFail()
{
	return isFailed;
}

void Cell::Lock()
{
	caption.setFillColor(sf::Color::Black); 
	isBlocked = true;
}

void Cell::UnLock()
{
	caption.setFillColor(sf::Color::Blue); 
	isBlocked = false;
}

bool Cell::IsLock()
{
	return isBlocked;
}