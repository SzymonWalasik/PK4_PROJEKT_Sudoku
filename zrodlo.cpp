#include <vector>
#include <functional>
#include <time.h>
#include <Windows.h>
#include "Initilize.h"
#include "Menu.h"

using namespace std;
using namespace placeholders;


vector<IDrawable*> objectsToDraw;
int main()
{
	auto menu = Menu();
	menu.init();

	return 0; 
}