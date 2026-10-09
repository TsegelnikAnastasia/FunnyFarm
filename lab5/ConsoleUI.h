#pragma once
#include <string>
using namespace std;
class ConsoleUI {
public:
	static void WaitForEnter();
	static void Clear();
	static void PrintHeader(const string& title);
	static void PrintCentered(const string& text);
	static void PrintSeparator();
	static void PrintGreen(const string& text);
	static void PrintRed(const string& text);
	static void PrintYellow(const string& text);
	static void PrintCyan(const string& text);
private:
	static const int Width = 60;
	static int DisplayLength(const string& s);
};
