#include "Colors.h"
#include <cstdlib>

namespace Colors {

    void Enable() { system(" "); }

    string Green(const string& text) { return "\033[32m" + text + "\033[0m"; }
    string Red(const string& text) { return "\033[31m" + text + "\033[0m"; }
    string Yellow(const string& text) { return "\033[33m" + text + "\033[0m"; }
    string Cyan(const string& text) { return "\033[36m" + text + "\033[0m"; }
    string Reset() { return "\033[0m"; }
}