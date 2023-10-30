#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

int main(int argc, char *argv[]) {
    std::string input = argv[1];
    std::string output = argv[2];
    //std::string input = "input.txt";
    //std::string output = "output.csv";
    std::ifstream input_file(input);

    if (!input_file.is_open()) {
        std::cout << "file is not opened";
        return 1;
    }

    std::map<std::string, int> words;
    std::string line;
    while (std::getline(input_file, line)) {
        std::istringstream input_line(line);
        std::string word;
        while(input_line >> word){
            std::string normal_word;
            for (char c: word) {
                if (std::isalnum(c)) {
                    normal_word += tolower(c);
                }
            }
            words[normal_word]++;
        }
    }
    input_file.close();

    std::vector<std::pair<std::string, int>> sortedWords;
    for (const auto& pair : words)
        sortedWords.emplace_back(pair);

    std::sort(sortedWords.begin(), sortedWords.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    std::ofstream output_file(output);
    output_file << "Word,Frequency,Frequency(%)" << std::endl;

    for (const auto& pair : sortedWords) {
        int totalWords = std::accumulate(sortedWords.begin(), sortedWords.end(),
                                         0, [](int sum, const auto& p) {
                    return sum + p.second;
                });

        double frequencyPercent = static_cast<double>(pair.second) / totalWords * 100.0;

        output_file << pair.first << "," << pair.second << "," << std::setprecision(2)
                   << std::fixed << frequencyPercent << std::endl;
    }
    output_file.close();

    std::cout << "Word count data has been saved to " << output << std::endl;

    return 0;
}
