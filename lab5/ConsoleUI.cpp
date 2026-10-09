#include "ConsoleUI.h"
#include "Colors.h"
#include <iostream>

#include <cstdlib>

using namespace std;
void ConsoleUI::WaitForEnter() {
	cout << "Нажмите Enter для продолжения..." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}
int ConsoleUI::DisplayLength(const string& s) {
	int len = 0;
	for (unsigned char c : s) len += (c >= 128) ? 2 : 1;
	return len;
}
void ConsoleUI::PrintHeader(const string& title) {
	string border = string(Width, '=');
	cout << Colors::Cyan(border) << endl;
	int titleLen = DisplayLength(title);
	int totalSpace = Width - titleLen;
	if (totalSpace < 0) {
		cout << title << endl;
		cout << border << endl;
		return;
	}
	int leftSpace = totalSpace / 2;
	
	cout << string(leftSpace, ' ') + title << endl;
	cout << Colors::Cyan(border) << endl;
}
void ConsoleUI::PrintSeparator() {
	cout << Colors::Cyan(string(Width, '=')) << endl;
}
void ConsoleUI::Clear() {
	system("cls");
}
void ConsoleUI::PrintCentered(const string& text) {
	int textLen = DisplayLength(text);
	int totalSpace = Width - textLen;
	if (totalSpace < 0) {
		cout << text << endl;
		return;
	}
	int leftSpace = totalSpace / 2;
	cout << string(leftSpace, ' ') << text << endl;
}
void ConsoleUI::PrintGreen(const string& text) {
	cout << Colors::Green("  " + text) << "\n";
}
void ConsoleUI::PrintRed(const string& text) {
	cout << Colors::Red("  " + text) << "\n";
}
void ConsoleUI::PrintYellow(const string& text) {
	cout << Colors::Yellow("  " + text) << "\n";
}
void ConsoleUI::PrintCyan(const string& text) {
	cout << Colors::Cyan("  " + text) << "\n";
}