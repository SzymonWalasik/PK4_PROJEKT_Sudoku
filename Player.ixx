//#include "Globals.h"
//#include "Cell.h"
//#include "GridController.h"

export module Player;
import <iostream>;
import <string>;
import <fstream>;
export class Player
{
public:
    Player(std::string name) : _name(name), _score(0) {}
    Player() : _score(0) {}

    std::string GetName() { return _name; }
    void SetScore(int score) { _score = score; }

    int score;

    friend std::istream& operator >> (std::istream& in, Player& obj)
    {
        in >> obj._name;
        in >> obj._score;
        return in;
    }
    friend std::ostream& operator << (std::ostream& out, const Player& obj)
    {
        out << obj._name << ' ';
        out << obj._score << std::endl;
        return out;
    }

private:
    std::string _name;
    int _score;
};


