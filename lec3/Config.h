#pragma once
#include "SoundProcessor.h"

class Config {
public:
    vector<string> commands;
    Config() = default;

    void processCommand(const string& command) {
        commands.push_back(command);
    }
    bool load(string& filename);

    const vector<string>& getCommands() const {
        return commands;
    }
};

