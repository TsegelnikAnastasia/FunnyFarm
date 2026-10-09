#pragma once
#include <string>
using namespace std;
namespace Colors {
	void Enable();
	string Green(const string& tetx);
	string Red(const string& text);
	string Yellow(const string& text);
	string Cyan(const string& text);
	string Reset();
}