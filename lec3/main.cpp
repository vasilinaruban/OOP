#include "Link.h"

int main(int argc, char* argv[]) {
    Config config;
    WavFile mainStream;
    WavFile additionalStream;

    if (argc == 2) {
        cout << "To run the program, enter the following command in the command line:" << endl;
        cout << "./Task_4 -c config.txt output.wav input1.wav [input2.wav]" << endl;
    }
    if (argc == 5) {
        string inputFilenameMain = argv[4];
        inputFilenameMain = inputFilenameMain;
        string outputFilename = argv[3];
        outputFilename = outputFilename;
        string configFilename = argv[2];
        configFilename = configFilename;
        mainStream.load(inputFilenameMain);
        if (mainStream.data.empty()) {
            cerr << "Failed to load WAV file." << endl;
            return -1;
        }
        if (!config.load(configFilename)) {
            cerr << "Error loading configuration file." << endl;
            return -1;
        }
        for (const auto& command : config.getCommands()) {
            auto processor = Link::createProcessor(command);
            if (processor) {
                processor->process(mainStream);
            }
        }
        mainStream.save(outputFilename);
        cout << "Conversion completed" << endl;
    }
    if (argc == 6) {
        string inputFilenameAdditional = argv[5];
        inputFilenameAdditional = inputFilenameAdditional;
        string inputFilenameMain = argv[4];
        inputFilenameMain = inputFilenameMain;
        string outputFilename = argv[3];
        outputFilename = outputFilename;
        string configFilename = argv[2];
        configFilename = configFilename;
        mainStream.load(inputFilenameMain);
        additionalStream.load(inputFilenameAdditional);
        if (mainStream.data.empty()) {
            cerr << "Failed to load WAV file." << endl;
            return -1;
        }
        if (!config.load(configFilename)) {
            cerr << "Error loading configuration file." << endl;
            return -1;
        }
        for (const auto& command : config.getCommands()) {
            auto processor = Link::createProcessor(command);
            if (processor) {
                processor->process(mainStream);
            }
        }
        mainStream.save(outputFilename);
        cout << "Conversion completed" << endl;
    }

    return 0;
}
