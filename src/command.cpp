#include "command.h"
#include <sstream>

using namespace std;

vector<string> Command::parse(const string& line) {
    vector<string> tokens;
    istringstream iss(line);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}