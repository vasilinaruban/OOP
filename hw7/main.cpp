//#include "test_runner.h"
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>

template<typename String>
using Group = std::vector<String>;

template<typename String>
using Char = typename String::value_type;

template<typename String>
std::set<Char<String>> split_word(String word) {
    std::set<Char<String>> Set;
    for (const auto &letter: word) {
        Set.insert(letter);
    }
    return Set;
}

template<typename String>
std::vector<Group<String>> GroupHeavyStrings(const std::vector<String> &strings) {
    std::map<std::set<Char<String>>, Group<String>> Map;
    for (const auto &word: strings){
        Map[split_word(word)].push_back(std::move(word));
    }
    std::vector<Group<String>> vec;
    for(const auto &key: Map){
        vec.push_back(key.second);
    }
    return vec;
}

int main(){
    std::vector<std::string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    for (const auto& group : groups)
    {
        for (const auto& word : group)
        {
            std::cout << word << " ";
        }
        std::cout << "\n";
    }
}