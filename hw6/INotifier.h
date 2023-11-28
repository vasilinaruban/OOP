#pragma once
#include <string>

class INotifier {
    virtual void Notify(const std::string& message) = 0;
};



