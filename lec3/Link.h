#pragma once
#include "Config.h"

class Link {
public:
    static unique_ptr<SoundProcessor> createProcessor(const string& command);
};

