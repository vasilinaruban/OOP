#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <cstdint>

using namespace std;

class WavFile {
public:
    char header[44];
    vector<int16_t> data;

    void load(string& filename);
    void save(string& filename);
};

