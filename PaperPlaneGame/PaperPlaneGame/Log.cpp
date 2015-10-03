#include "Log.h"

#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_TEAL 3
#define DARK_RED 4
#define DARK_PURPLE 5
#define DARK_YELLOW 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define BLUE 9
#define GREEN 10
#define TEAL 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15

#define WHITE_TEXT_BLACK_BACKGROUND WHITE + BLACK * 16
#define RED_TEXT_BLACK_BACKGROUND RED + BLACK * 16

namespace Log
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void Message(const std::string message)
	{
		SetConsoleTextAttribute(hConsole, WHITE_TEXT_BLACK_BACKGROUND);
		std::cout << message << std::endl;
	}

	void Error(const std::string message)
	{
		SetConsoleTextAttribute(hConsole, RED_TEXT_BLACK_BACKGROUND);
		std::cout << message << std::endl;
	}
}
