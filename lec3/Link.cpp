#include "Link.h"

unique_ptr<SoundProcessor> Link::createProcessor(const string &command) {
    istringstream iss(command);
    string cmd;
    iss >> cmd;
    if (cmd == "mute") {
        int start, end;
        iss >> start >> end;
        return make_unique<MuteCommand>(start, end);
    }
    else if (cmd == "reverse") {
        int start, end;
        iss >> start >> end;
        return make_unique<ReverseCommand>(start, end);
    }
    else if (cmd == "mix") {
        int delaySeconds;
        string filename;
        iss >> filename >> delaySeconds;
        WavFile additionalStream;
        additionalStream.load(filename);
        if (additionalStream.data.empty()) {
            cerr << "Failed to open the WAV file." << endl;
            return nullptr;
        }
        return make_unique<MixCommand>(additionalStream, delaySeconds);
    }
    else {
        cerr << "Unknown command: " << cmd << endl;
        return nullptr;
    }
}
