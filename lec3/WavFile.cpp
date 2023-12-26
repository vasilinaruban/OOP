#include "WavFile.h"

void WavFile::load(string &filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    file.read(header, sizeof(header));
    while (file) {
        int16_t sample;
        file.read(reinterpret_cast<char *>(&sample), sizeof(sample));
        data.push_back(sample);
    }
    file.close();
}

void WavFile::save(string &filename) {
    ofstream file(filename, ios::binary);
    file.write(header, sizeof(header));
    for (int16_t& sample : data) {
        file.write(reinterpret_cast<char*>(&sample), sizeof(sample));
    }
    file.close();
}
