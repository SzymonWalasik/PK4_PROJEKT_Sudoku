#include"Button.h"

Button::Button(sf::RenderWindow* _window, std::string _caption, sf::Vector2f pos, sf::Vector2f size, sf::RenderStates* _renderStates)	//stworzenie guzików jako obiekty
{
	window = _window;
	renderStates = _renderStates;

	texture = sf::Texture();
	texture.loadFromFile("Images/png_buttons_87302.png");

	shape = sf::RectangleShape(size);
	shape.setTexture(&texture);
	shape.setPosition(pos);

	if (font.loadFromFile("Fonts/OpenSans-Regular.ttf")) {
		std::cout << "Loaded Font successful!" << std::endl;
	}
	caption.setFont(font);
	caption.setFillColor(sf::Color::Black);
	caption.setCharacterSize(25);
	caption.setString(_caption);
	sf::FloatRect b = caption.getGlobalBounds(); 
	caption.setPosition(shape.getPosition().x + shape.getSize().x / 2 - b.width / 2, shape.getPosition().y + b.height/ 1.3); 

	collider.position = shape.getPosition(); 
	collider.size = shape.getSize(); 
}

Button::Button(sf::RenderWindow* _window, std::string _caption, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
	window = _window;
	shape.setSize(buttonSize);
	shape.setFillColor(bgColor);

	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;

	caption.setString(_caption);
	caption.setCharacterSize(charSize);
	caption.setFillColor(textColor);
}

void Button::setFont(sf::Font& fonts) {
	caption.setFont(fonts);
}

void Button::setBackColor(sf::Color color) {
	shape.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	caption.setFillColor(color);
}

void Button::setPosition(sf::Vector2f point) {
	shape.setPosition(point);

	float xPos = (point.x + btnWidth / 2) - (caption.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight / 2.2) - (caption.getLocalBounds().height / 2);
	caption.setPosition(xPos, yPos);
}

void Button::drawTo() {
	window->draw(shape);
	window->draw(caption);
}

bool Button::isMouseOver() {
	sf::RenderWindow& refWindow = *window;

	int mouseX = sf::Mouse::getPosition(refWindow).x;
	int mouseY = sf::Mouse::getPosition(refWindow).y;

	int btnPosX = shape.getPosition().x;
	int btnPosY = shape.getPosition().y;

	int btnxPosWidth = shape.getPosition().x + shape.getSize().x;
	int btnyPosHeight = shape.getPosition().y + shape.getSize().y;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}

void Button::ProcessEvent(sf::Event event)
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	float f = 1 / *(renderStates->transform.getMatrix());
	mousePos = sf::Vector2f(f * (float)(mousePos.x), f * (float)(mousePos.y));

	if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) 
	{
		if (collider.IsPointInside(mousePos)) 
		{
			Click(); 
		}
	}
}

void Button::Draw()
{
	window->draw(shape, *renderStates); 
	window->draw(caption, *renderStates); 
}