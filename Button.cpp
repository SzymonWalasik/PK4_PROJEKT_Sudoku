#include"Button.h"


Button::Button(sf::RenderWindow* _window, sf::RenderStates* _renderStates, std::string _caption, sf::Vector2f pos, sf::Vector2f size)
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
Button::Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
	button.setSize(buttonSize);
	button.setFillColor(bgColor);

	// Get these for later use:
	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;

	text.setString(btnText);
	text.setCharacterSize(charSize);
	text.setFillColor(textColor);
}
void Button::setFont(sf::Font& fonts) {
	text.setFont(fonts);
}

void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f point) {
	button.setPosition(point);

	float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + btnWidth;
	int btnyPosHeight = button.getPosition().y + btnHeight;

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