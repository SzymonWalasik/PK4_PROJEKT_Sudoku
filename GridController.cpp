#include "GridController.h"

extern std::vector<IDrawable*> objectsToDraw;	//ten obiekt jest zadeklarowany z Ÿródle

template <typename T>
std::string toString(T arg)		//konwersja typu na string
{
	std::stringstream ss;
	ss << arg;
	return ss.str();
}

GridController::GridController(sf::RenderWindow* _window, sf::RenderStates* _renderStates, sf::Text* _winText)	//konstruktor tworz¹cy kolejno wszystkie komórki macierzy
{
	window = _window;
	renderStates = _renderStates;
	winText = _winText;
	
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			
			matrix[y][x] = new Cell(_window, _renderStates, cellImage, sf::Vector2f(64, 64));
			int n = (x + 1) + ((y % 3) * 3) + (y / 3); 
			if (n > 9) {
				n -= 9;
			}
			matrix[y][x]->correctValue = n;
			matrix[y][x]->SetUserNumber(n);
			matrix[y][x]->SetPosition(sf::Vector2f(x * 64 + upperLeftCornerX, y * 64 + upperLeftCornerY));
			matrix[y][x]->SetMatrixPosition(y, x);
			objectsToDraw.push_back(matrix[y][x]); 
		}
	}
	Mix(); 
}

void GridController::ProcessEvent(sf::Event event)		//funkcja odpowiedzialna za wychwytywanie pozycji myszy oraz zmiany wartoœci wartoœci w komórkach macierzy
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	float f = 1 / *(renderStates->transform.getMatrix());	//funkcja OpenGL getMatrix() zwraca wskaŸnik na array, a zmienna f odpowiada za przekazanie wskaŸnika za pomoc¹ którego jesteœmy w stanie okreœliæ po³o¿enie myszy
	mousePos = sf::Vector2f(f * (float)(mousePos.x), f * (float)(mousePos.y));

	if (event.type == sf::Event::MouseButtonReleased &&		//inkrementacja wartosci w komorkach
		event.key.code == sf::Mouse::Left) 
	{
		
		for (int y = 0; y < 9; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				if (matrix[y][x]->collider.IsPointInside(mousePos)) 
				{
					if ((matrix[y][x]->GetUserNumber() + 1) == matrix[y][x]->correctValue)
					{
						scoreCounter++;
					}

					int n = matrix[y][x]->GetUserNumber() + 1; 
					if (n > 9) 
						n = 0;
					matrix[y][x]->SetUserNumber(n); 

					CheckWin(); 
					return;
				}
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased &&		//dekrementacja wartosci w komorkach
		event.key.code == sf::Mouse::Right)
	{

		for (int y = 0; y < 9; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				if (matrix[y][x]->collider.IsPointInside(mousePos))
				{
					if ((matrix[y][x]->GetUserNumber() - 1) == matrix[y][x]->correctValue)
					{
						scoreCounter++;
					}
					int n = matrix[y][x]->GetUserNumber() - 1;
					if (n < 0)
						n = 9;
					matrix[y][x]->SetUserNumber(n);

					CheckWin();
					return;
				}
			}
		}
	}
}

void GridController::ShowScores(sf::Text& txt)
{
	fs::path pth = fs::current_path();		//zastosowanie filesystem do ustawienia œcie¿ki do pliku projektu
	pth.append("Score\\score.dat");			//dodanie do aktualnej œcie¿ki adresu pliku przechowuj¹cego wyniki u¿ytkowników

	std::ifstream infile(pth);
	std::string line;
	int counter = 0;
	v_scores.clear();						//przy ka¿dym odczycie z pliku czyœcimy go i zapisujemy wartoœci ponownie 

	while (std::getline(infile, line))	
	{
		AddScoresToVector(line);
	}
	std::sort(v_scores.begin(), v_scores.end(),std::greater<>());	//sortujemy wektor na podstawie wyników uzyskanych przez graczy
	for (int i = 0; i < v_scores.size(); i++)		//pêtla wypisuj¹ca top 10 wyników
	{
		if (counter > 9) {
			break;
		}
		txt.setPosition(120, 110 + 30 * i);
		txt.setString(v_scores[i].second);
		window->draw(txt);
		txt.setString(toString(v_scores[i].first));
		txt.setPosition(250, 110 + 30 * i);
		window->draw(txt);
		counter++;
	}
}
void GridController::AddScoresToVector(std::string line)		//za³adowanie zawartoœci pliku wyników do wektora
{
	std::string str1;
	std::string str2;

	int pos = line.find(" ");

	str1 = line.substr(0, pos);
	str2 = line.substr(pos + 1);

	int score = std::stoi(str2);

	v_scores.push_back(std::make_pair(score, str1));
}

void GridController::CheckWin()
{
	auto isCorrect = [&](Cell* cell)		//funkcja lambda
	{
		int x = cell->GetXMatrixPosition();
		int y = cell->GetYMatrixPosition();
		int checkingNum = matrix[y][x]->GetUserNumber();
		int offsetX = x - (x % 3);
		int offsetY = y - (y % 3);

		for (int i = 0; i < 9; i++)
		{
			if (i != x && checkingNum == matrix[y][i]->GetUserNumber())		//sprawdzamy mo¿liwoœæ kolizji cyfr w kolumnie
			{
				matrix[y][x]->SetFail(true);
				return false;
			}
			if (i != y && checkingNum == matrix[i][x]->GetUserNumber())		//sprawdzamy mo¿liwoœæ kolizji cyfr w wierszu
			{
				matrix[y][x]->SetFail(true);
				return false;
			}
			if (((i / 3 + offsetY) != y || (i % 3 + offsetX) != x) &&		//sprawdzamy mo¿liwoœæ kolizji cyfr w kwadracie 3x3
				checkingNum == matrix[i / 3 + offsetY][i % 3 + offsetX]->GetUserNumber())
			{
				matrix[y][x]->SetFail(true);
				return false;
			}
		}
		matrix[y][x]->SetFail(false);
		return true;
	};

	bool res = true;
	for (auto& row : matrix)		//sprawdzamy poprawnoœæ wszystkich komórek macierzy 
	{
		for (auto ele : row | std::views::transform(isCorrect))		//zastosowanie ranges do porównania wpisanych wartoœci do poprawnych
		{
			if (!ele)
				res = false;
		}
	}

	if (res)
	{
		std::cout << "Win game" << std::endl;
		winText->setString("You WON!!!");
	}
}

void GridController::ChangeDifficult()		//kolejnosc poziomow trudnosci przy zmianie
{
	if (difficultGame == Difficult::Easy) {
		difficultGame = Difficult::Normal;
	}
	else if (difficultGame == Difficult::Normal) {
		difficultGame = Difficult::Hard;
	}
	else if (difficultGame == Difficult::Hard) {
		difficultGame = Difficult::Easy;
	}
		
}

void GridController::Mix()
{
	winText->setString("SUDOKU");
	for (int y = 0; y < 9; y++)			//odblokowujemy wszystkie komórki i ustawiamy wartoœci na domyœlne (0)
	{
		for (int x = 0; x < 9; x++)
		{
			matrix[y][x]->UnLock(); 
			matrix[y][x]->SetUserNumber(0); 
		}
	}

	for (int i = 0; i < 15; i++)		//wykonujemy 15 operacji na macierzy w pseudo losowej kolejnoœci
	{
		switch (rand() % 5) 
		{
		case 0: Transposion(); break;
		case 1: SwapRowsSmall(); break;
		case 2: SwapColumsSmall(); break;
		case 3: SwapRowsArea(); break;
		case 4: SwapColumsArea(); break;
		}
	}

	int counterLocked = 0;
	int randX, randY;
	while (counterLocked < (int)difficultGame)		//wype³nienie czêœci komórek na pocz¹tku rozgrywki
	{
		randX = rand() % 9; 
		randY = rand() % 9;
		if (matrix[randY][randX]->IsLock() == false) 
		{
			counterLocked++; 
			matrix[randY][randX]->SetUserNumber(matrix[randY][randX]->correctValue); 
			matrix[randY][randX]->Lock(); 
		}
	}
}
void GridController::Hint(){
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			if (matrix[y][x]->IsLock()== false && matrix[y][x]->GetUserNumber() == 0) {
				matrix[y][x]->SetUserNumber(matrix[y][x]->correctValue);
				hintCounter++;
				CheckWin();
				return;
			}
		}

	}
}
int GridController::GetCorrectlyFilledCells() {			// zwraca iloœæ poprawnie wype³nionych komórek
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			if (matrix[y][x]->GetUserNumber() == matrix[y][x]->correctValue) {
				scoreCounter++;
			}
		}
	}
	return scoreCounter;
}

void GridController::ExitGame() {
	shouldCloseApp = true;
	std::ofstream outfile;
	fs::create_directory("Score");		// zastosowanie filesystem do stworzenia katalogu
	outfile.open("Score/score.dat", std::ios::app);
	_player.SetScore(scoreCounter*10 - hintCounter*30);
	outfile << _player;
	outfile.close();
}

void GridController::Transposion()
{
	int corNum = 0;
	int usrNum = 0;
	for (int y = 0; y < 9; y++)
	{
		for (int x = y + 1; x < 9; x++)
		{
			corNum = matrix[x][y]->correctValue;
			usrNum = matrix[x][y]->GetUserNumber();

			matrix[x][y]->correctValue = matrix[y][x]->correctValue;
			matrix[x][y]->SetUserNumber(matrix[y][x]->GetUserNumber());

			matrix[y][x]->correctValue = corNum;
			matrix[y][x]->SetUserNumber(usrNum);
		}
	}
}

void GridController::SwapRowsSmall()
{
	int corNum = 0;
	int usrNum = 0;
	int area = rand() % 3;
	int line1 = rand() % 3;
	int line2 = rand() % 3;
	while (line2 == line1)
		line2 = rand() % 3;

	line1 += area * 3;
	line2 += area * 3;

	for (int x = 0; x < 9; x++)
	{
		
		corNum = matrix[line1][x]->correctValue;
		usrNum = matrix[line1][x]->GetUserNumber();

		matrix[line1][x]->correctValue = matrix[line2][x]->correctValue;
		matrix[line1][x]->SetUserNumber(matrix[line2][x]->GetUserNumber());

		matrix[line2][x]->correctValue = corNum;
		matrix[line2][x]->SetUserNumber(usrNum);
	}
}

void GridController::SwapColumsSmall()
{
	int corNum = 0;
	int usrNum = 0;
	int area = rand() % 3;
	int col1 = rand() % 3;
	int col2 = rand() % 3;
	while (col2 == col1)
		col2 = rand() % 3;

	col1 += area * 3;
	col2 += area * 3;

	for (int y = 0; y < 9; y++)
	{
		
		corNum = matrix[y][col1]->correctValue;
		usrNum = matrix[y][col1]->GetUserNumber();

		matrix[y][col1]->correctValue = matrix[y][col2]->correctValue;
		matrix[y][col1]->SetUserNumber(matrix[y][col2]->GetUserNumber());

		matrix[y][col2]->correctValue = corNum;
		matrix[y][col2]->SetUserNumber(usrNum);
	}
}

void GridController::SwapRowsArea()
{
	int corNum = 0;
	int usrNum = 0;
	int area1 = rand() % 3;
	int area2 = rand() % 3;
	while (area2 == area1)
		area2 = rand() % 3;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			
			corNum = matrix[area1 * 3 + y][x]->correctValue;
			usrNum = matrix[area1 * 3 + y][x]->GetUserNumber();

			matrix[area1 * 3 + y][x]->correctValue = matrix[area2 * 3 + y][x]->correctValue;
			matrix[area1 * 3 + y][x]->SetUserNumber(matrix[area2 * 3 + y][x]->GetUserNumber());

			matrix[area2 * 3 + y][x]->correctValue = corNum;
			matrix[area2 * 3 + y][x]->SetUserNumber(usrNum);
		}
	}
}

void GridController::SwapColumsArea()
{
	int corNum = 0;
	int usrNum = 0;
	int area1 = rand() % 3;
	int area2 = rand() % 3;
	while (area2 == area1)
		area2 = rand() % 3;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			
			corNum = matrix[y][area1 * 3 + x]->correctValue;
			usrNum = matrix[y][area1 * 3 + x]->GetUserNumber();

			matrix[y][area1 * 3 + x]->correctValue = matrix[y][area2 * 3 + x]->correctValue;
			matrix[y][area1 * 3 + x]->SetUserNumber(matrix[y][area2 * 3 + x]->GetUserNumber());

			matrix[y][area2 * 3 + x]->correctValue = corNum;
			matrix[y][area2 * 3 + x]->SetUserNumber(usrNum);
		}
	}
}
