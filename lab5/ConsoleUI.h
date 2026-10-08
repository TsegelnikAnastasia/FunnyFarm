#pragma once
#include <string>
using namespace std;
class ConsoleUI {
public:
	static void Clear();
	static void PrintHeader(const string& title);
	static void PrintCentered(const string& text);
	static void PrintLine(const string&text);
	static void PrintSeparator();
private:
	static const int Width = 60;
	static int DisplayLength(const string& s);
};
