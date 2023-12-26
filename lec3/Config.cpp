#include "Config.h"

bool Config::load(string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error loading configuration file: " << filename << endl;
        return false;
    }
    string cmd, arg1, arg2, line;
    while (file >> cmd >> arg1 >> arg2) {
        line = cmd + " " + arg1 + " " + arg2;
        processCommand(line);
    }
    file.close();
    return true;
}
