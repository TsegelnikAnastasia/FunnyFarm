#include "ConsoleUI.h"
#include <iostream>
#include <cstdlib>

using namespace std;
int ConsoleUI::DisplayLength(const string& s) {
	int len = 0;
	for (unsigned char c : s) len += (c >= 128) ? 2 : 1;
	return len;
}
void ConsoleUI::PrintHeader(const string& title) {
	string border = string(Width, '=');
	cout << border << endl;
	int titleLen = DisplayLength(title);
	int totalSpace = Width - titleLen;
	if (totalSpace < 0) {
		cout << title << endl;
		cout << border << endl;
		return;
	}
	int leftSpace = totalSpace / 2;
	
	cout << string(leftSpace, ' ') << title << endl;
	cout << border << endl;
}
void ConsoleUI::PrintLine(const string& text) {
	cout << "  " << text << endl;
}
void ConsoleUI::PrintSeparator() {
	cout << string(Width, '=') << endl;
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