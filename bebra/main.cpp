#include <iostream>
#include <sstream>
#include "Rational.h"

int main() {
    std::string input;
    getline(std::cin, input);
    std::stringstream ss(input);
    Rational r1, r2;
    char operation;
    try {
        ss >> r1;
        ss.ignore(1);
        ss >> operation;
        ss.ignore(1);
        ss >> r2;
    } catch (std::exception& ex) {
        std::cout << "Invalid argument" << std::endl;
        return 1;
    }
    Rational res;
    try {
        switch (operation) {
            case '+': {
                res = r1 + r2;
                break;
            }
            case '-': {
                res = r1 - r2;
                break;
            }
            case '*': {
                res = r1 * r2;
                break;
            }
            case '/': {
                res = r1 / r2;
                break;
            }
            default: {
                std::cout << "Invalid operation" << std::endl;
            }
        }
    }
    catch (std::exception& ex) {
        std::cout << "Division by zero" << std::endl;
        return 2;
    }
    std::cout << res;
    return 0;
}
